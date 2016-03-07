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

void GameTree::delete_next(void) {
    if (next != NULL) {
        for (int i = 0; i < next->size(); i++) {
            delete (*next)[i].first;
            delete (*next)[i].second;
        }
        delete next;
        next = NULL;
    }
}

GameTree::~GameTree() {
    delete_next();
    delete board;
}

int GameTree::assess() {
    // If this is the end of the line, just assess the board for the current
    // side.
    if (next == NULL || next->size() == 0)
        return board->assess(side, testingMinimax);

    // Otherwise, get the assessment for this side (the negative of the
    // assessments for the other side) for each possible next board, and take
    // the maximum of those.
    int curr_score;
    int max_score = -(*next)[0].second->assess();

    for (int i = 1; i < next->size(); i++) {
        curr_score = -(*next)[i].second->assess();
        if (curr_score > max_score) max_score = curr_score;
    }

    return max_score;
}

Move *GameTree::getBestMove() {
    // If this is the end of the line, pass.
    if (next == NULL || next->size() == 0) return NULL;   

    // Otherwise, take the negative of all of the assessments of the next
    // boards (equivalent to the assessment for this side) and return the move
    // that maximizes that.
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

    // If this is the bottom of the tree,
    if (next == NULL) {

        // Create a vector of all of the possible trees down from here.
        next = new vector<pair<Move *, GameTree *> >();
        Side other = side == WHITE? BLACK: WHITE;

        // Start with a vector all legal moves.
        std::vector<Move *> *legals = board->getLegals(side);
        Board *temp;
        GameTree *next_tree;

        // For each of those,
        for (int i = 0; i < legals->size(); i++) {

            // create the resulting board
            temp = board->copy();
            temp->doMove((*legals)[i], side);

            // and the resulting tree (to `c - 1` levels, because we just
            // added a level),
            next_tree = new GameTree(temp,  other,
                                     c - 1, originalLevel, testingMinimax);

            // And add those to the next level.
            next->push_back(pair<Move *, GameTree *>((*legals)[i],
                                                     next_tree));
        }

        // Clean up.
        delete legals;
        return;
    }

    // If this is not the bottom of the tree, just recurse into the next
    // level.
    for (int i = 0; i < next->size(); i++) (*next)[i].second->addPly(c);
}

void GameTree::doMove(Move *move) {
    // If the other player passes, we might as well throw everything out.
    if (move == NULL) {
        side = side == WHITE? BLACK: WHITE;

        delete_next();

        addPly(originalLevel);
        return;
    }

    // If this is the end of the line (which should probably never happen),
    // just change the current player.
    if (next == NULL) {
        cerr << "WARNING: making move at the end of the tree." << endl;
        cerr << "This is probably not the intended behavior." << endl << endl;
        board->doMove(move, side);
        side = side == WHITE? BLACK: WHITE;

        return;
    }

    for (int i = 0; i < next->size(); i++) {

        // If the results of the move have already been calculated,
        if (*move == *((*next)[i].first)) {
            // Transfer a bunch of crap from that branch to this one.  We do
            // this carefully so that we copy as few things as possible while
            // avoiding as much duplicate computation as possible--we want to
            // copy over all of the sublevels from the subtree, but we don't
            // want to do it the naive way by simply allocating a new tree and
            // copying everything over.
            
            // The tree we want to copy into this one.
            GameTree *new_tree = (*next)[i].second;

            // Make sure `new_tree` won't be deleted
            (*next)[i].second = NULL;
            // when we free the subtrees.
            delete_next();

            // Copy over the tree from one level down (pointerwise, so this is
            // not an expensive operation).
            next = new_tree->next;
            new_tree->next = NULL;

            // Do a similar operation with the board.
            delete board;
            board = new_tree->board;
            new_tree->board = NULL;

            // Change sides after each move.
            side = new_tree->side;

            // We're done with this.
            delete new_tree;

            // Add a new level to keep the tree at the desired depth.
            addPly(1);

            // No point in continuing the search.
            return;
        }
    }
}

void GameTree::doOpponentMove(Move *move) {
    doMove(move);
}
