#include "player.h"

Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = Board();   
    this->side = side;
    opponent = side == BLACK? WHITE: BLACK;
    srand(time(NULL));
}

Player::~Player() {
}

Move *Player::doMove(Move *opponentsMove, int msLeft) {
    board.doMove(opponentsMove, opponent);

    std::vector<Move *> *legals = board.getLegals(side);
    Move curr(0, 0);

    if (legals->size() == 0) return NULL;

    Board *temp = board.copy();
    int max_score;
    int curr_score;

    Move *max_move = (*legals)[0];
    temp->doMove(max_move, side);
    max_score = temp->assess(side);
    delete temp;

    for (int i = 1; i < legals->size(); i++) {
        temp = board.copy();
        temp->doMove((*legals)[i], side);

        curr_score = temp->assess(side);
        if (temp->assess(side) > max_score) {
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
