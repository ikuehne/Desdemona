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

    if (legals->size() == 0) {
        return NULL;
    }

    Move *rand_item = (*legals)[rand() % legals->size()];
    curr.setX(rand_item->x);
    curr.setY(rand_item->y);
    
    for (int i = 0; i < legals->size(); i++) {
        delete (*legals)[i];
    }

    delete legals;

    if (!board.checkMove(&curr, side)) {
        return NULL;
    }

    board.doMove(&curr, side);

    return new Move(curr.getX(), curr.getY());
}
