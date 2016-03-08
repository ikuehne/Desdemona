#include "player.h"
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    this->side = side;

    tree = NULL;

    ifstream file(BASIC_WEIGHT_FILE);
    std::string line;
    for (int i = 0; i < TOTAL_WEIGHTS; i++)
    {
        std::getline(file, line);

        int weight = std::stoi(line);
        weights[i] = weight;
    }


    startingBoard = new Board(weights);
}


Player::~Player() {
    if (tree == NULL) {
        delete startingBoard;
    }
    delete tree;
}

Move *Player::doMove(Move *opponentsMove, int msLeft) {
    int ply = testingMinimax? 2: MAX_PLY;

    // If we're black and this is white's first move,
    if (tree == NULL && opponentsMove != NULL)
        // Change the starting board before creating the tree.
        startingBoard->doMove(opponentsMove, side == WHITE? BLACK: WHITE);

    // If this is the first move, create the tree.
    if (tree == NULL)
        tree = new GameTree(startingBoard, side, ply, testingMinimax);

    // Otherwise, do the move on the tree.
    else tree->doOpponentMove(opponentsMove);

    Move *move = tree->getBestMove();
    tree->doMove(move);
    return move;
}
