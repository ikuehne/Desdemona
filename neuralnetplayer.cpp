#include "neuralnetplayer.h"

NeuralNetPlayer::NeuralNetPlayer(Side side, char* weightFile) {

    testingMinimax = false;
    this->side = side;

    tree = NULL;

    ifstream file(weightFile);
    std::string line;
    for (int i = 0; i < TOTAL_WEIGHTS; i++)
    {
        std::getline(file, line);

        int weight = std::stoi(line);
        weights[i] = weight;
    }

    startingBoard = new Board(weights);
}

NeuralNetPlayer::~NeuralNetPlayer() {
    if (tree == NULL) {
        delete startingBoard;
    }
    delete tree;
}

Move *NeuralNetPlayer::doMove(Move *opponentsMove, int msLeft) {
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
