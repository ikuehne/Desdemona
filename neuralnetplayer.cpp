#include "neuralnetplayer.h"

NeuralNetPlayer::NeuralNetPlayer(Side side, char* weightFile) {

    testingMinimax = false;
    this->side = side;
    opponent = side == BLACK? WHITE: BLACK;
    srand(time(NULL));

    ifstream file(weightFile);
    std::string line;
    for (int i = 0; i < TOTAL_WEIGHTS; i++)
    {
        std::getline(file, line);

        int weight = std::stoi(line);
        weights[i] = weight;
    }

    board = Board(weights);
}

NeuralNetPlayer::~NeuralNetPlayer() {
}

Move *NeuralNetPlayer::doMove(Move *opponentsMove, int msLeft) {
    board.doMove(opponentsMove, opponent);

    std::vector<Move *> *legals = board.getLegals(side);
    Move curr(0, 0);

    if (legals->size() == 0) return NULL;

    Board *temp = board.copy();
    int max_score;
    int curr_score;

    Move *max_move = (*legals)[0];
    temp->doMove(max_move, side);
    max_score = temp->netAssess(side, testingMinimax);
    delete temp;

    for (int i = 1; i < legals->size(); i++) {
        temp = board.copy();
        temp->doMove((*legals)[i], side);

        curr_score = temp->netAssess(side, testingMinimax);
        if (curr_score > max_score) {
            max_score = curr_score;
            max_move = (*legals)[i];
        }
        delete temp;
    }

    curr.setX(max_move->x);
    curr.setY(max_move->y);
    
    for (int i = 0; i < legals->size(); i++) delete (*legals)[i];

    delete legals;

    if (!board.checkMove(&curr, side)) return NULL;

    board.doMove(&curr, side);

    return new Move(curr.getX(), curr.getY());
}
