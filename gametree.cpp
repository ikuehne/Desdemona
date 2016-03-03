#include "gametree.h"

GameTree::GameTree(Board *board, Side side, int level, bool testingMinimax) {
    // Copy over some parameters.
    this->board = board;
    this->side = side;
    this->testingMinimax = testingMinimax;

    // If this is the bottom of the tree, make sure to properly indicate it.
    // Set the worst score (for minimax) to the current score.
    if (level == 0) {
        next = NULL;
        best_move = NULL;
        worst_score = new int(board->assess(side, testingMinimax));
        return;
    }

    next = new vector<pair<Move *, GameTree *> >();

    std::vector<Move *> *legals = board->getLegals(side);

    if (legals->size() == 0) {
        worst_score = new int(board->assess(side, testingMinimax));
    }

    Side other = side == WHITE? BLACK: WHITE;

    Board *temp;
    GameTree *next_tree;
    for (int i = 0; i < legals->size(); i++) {
        temp = board->copy();
        temp->doMove((*legals)[i], side);
        next_tree = new GameTree(temp, other,
                                 level - 1, testingMinimax);
        next->push_back(pair<Move *, GameTree *>((*legals)[i], next_tree));
    }

    best_move = NULL;
    worst_score = NULL;
    delete legals;
}

GameTree::~GameTree() {
    delete board;
    delete next;
    delete worst_score;
    delete best_move;
}

int GameTree::assess() {
    if (worst_score) return *worst_score;

    int curr_score;
    int min_score = (*next)[0].second->assess();
    int max_score = min_score;
    Move *best_move = (*next)[0].first;

    for (int i = 1; i < next->size(); i++) {
        curr_score = (*next)[i].second->assess();
        if (curr_score < min_score) min_score = curr_score;

        if (curr_score > max_score) {
            max_score = curr_score;
            best_move = (*next)[i].first;
        }
    }

    worst_score = new int(min_score);

    return min_score;
}

Move *GameTree::get_best_move() {
    assess();
    return best_move;
}
