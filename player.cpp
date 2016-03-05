#include "player.h"
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    this->side = side;

    tree = NULL;
    startingBoard = new Board();
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
        startingBoard->doMove(opponentsMove, side);
        tree = new GameTree(startingBoard, side, 2, testingMinimax);
    } else {
        tree->doMove(opponentsMove);
    }

    Move *move = tree->getBestMove();
    tree->doMove(move);
    return move;
}
