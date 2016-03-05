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
    if (tree == NULL && opponentsMove == NULL) {
        tree = new GameTree(startingBoard, side, 2, testingMinimax);
    } else if (tree == NULL) {
        startingBoard->doMove(opponentsMove, side == WHITE? BLACK: WHITE);
        tree = new GameTree(startingBoard, side, 2, testingMinimax);
    } else {
        tree->doMove(opponentsMove);
    }

    Move *move = tree->getBestMove();
    tree->doMove(move);
    return move;
}
