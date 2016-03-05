#include "gametree.h"

GameTree::GameTree(Board *board, Side side, int level, bool testingMinimax) {
    // Copy over some parameters.
    this->board = board;
    this->side = side;
    this->testingMinimax = testingMinimax;
    next = NULL;
    originalLevel = level;

    addPly(level);
}

GameTree::GameTree(Board *board, Side side, int level,
                   int originalLevel, bool testingMinimax) {
    // Copy over some parameters.
    this->board = board;
    this->side = side;
    this->testingMinimax = testingMinimax;
    this->originalLevel = originalLevel;
    next = NULL;

    addPly(level);
}

GameTree::~GameTree() {
    if (next) {
        // Clean up each of the subtrees,
        for (int i = 0; i < next->size(); i++) {
            delete (*next)[i].first;
            delete (*next)[i].second;
        }
    }

    // And then the obvious stuff.
    delete next;
    delete board;
}

int GameTree::assess() {
    if (next == NULL) {
        return board->assess(side, testingMinimax);
    }
 
    if (next->size() == 0) {
        return board->assess(side, testingMinimax);
    }

    int curr_score;
    int max_score = -(*next)[0].second->assess();

    for (int i = 1; i < next->size(); i++) {
        curr_score = -(*next)[i].second->assess();
        if (curr_score > max_score) max_score = curr_score;
    }

    return max_score;
}

Move *GameTree::getBestMove() {
    if (next == NULL || next->size() == 0) return NULL;   

    int curr_score;
    int best_score = -(*next)[0].second->assess();

    Move *best_move = (*next)[0].first;
    
    for (int i = 1; i < next->size(); i++) {
        curr_score = -(*next)[i].second->assess();
        if (curr_score > best_score) {
            best_score = curr_score;
            best_move = (*next)[i].first;
        }
    }

    return new Move(*best_move);
}

void GameTree::addPly(int c) {
    if (c == 0) return;

    if (next == NULL) {
        next = new vector<pair<Move *, GameTree *> >();
        Side other = side == WHITE? BLACK: WHITE;
        std::vector<Move *> *legals = board->getLegals(side);
        Board *temp;
        GameTree *next_tree;
        for (int i = 0; i < legals->size(); i++) {
            temp = board->copy();
            temp->doMove((*legals)[i], side);
            next_tree = new GameTree(temp,  other,
                                     c - 1, originalLevel, testingMinimax);
            next->push_back(pair<Move *, GameTree *>(new Move(*(*legals)[i]),
                                                     next_tree));
        }
        for (int i = 0; i < legals->size(); i++) {
            delete (*legals)[i];
        }

        delete legals;
        return;
    }

    for (int i = 0; i < next->size(); i++) {
        (*next)[i].second->addPly(c);
    }
}

void GameTree::doMove(Move *move) {
    if (move == NULL) {
        side = side == WHITE? BLACK: WHITE;
        delete next;
        next = NULL;

        addPly(originalLevel);
        return;
    }

    if (next == NULL) {
        board->doMove(move, side);
        side = side == WHITE? BLACK: WHITE;

        return;
    }

    for (int i = 0; i < next->size(); i++) {

        // If the results of the move have already been calculated,
        if (*move == *((*next)[i].first)) {
            // Transfer a bunch of crap from that branch to this one,
            GameTree *new_tree = (*next)[i].second;
            vector<pair<Move *, GameTree *> > *old_next = next;
            next = new_tree->next;
            new_tree->next = NULL;

            board = new_tree->board;
            new_tree->board = NULL;
            side = new_tree->side;

            // And then clean it all up.
            for (int j = 0; j < old_next->size(); j++) {
                delete (*old_next)[j].first;
                delete (*old_next)[j].second;
            }
            delete old_next;
        }
    }
    addPly(1);
}

void GameTree::doOpponentMove(Move *move) {
    doMove(move);
}
