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

    std::vector<Move *> legals;
    Move curr(0, 0);
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            curr.setX(x);
            curr.setY(y);
            if (board.checkMove(&curr, side)) {
                legals.push_back(new Move(x, y));
            }
        }
    }

    if (legals.size() == 0) {
        return NULL;
    }

    Move *rand_item = legals[rand() % legals.size()];
    curr.setX(rand_item->x);
    curr.setY(rand_item->y);
    
    for (int i = 0; i < legals.size(); i++) {
        delete legals[i];
    }

    if (!board.checkMove(&curr, side)) {
        return NULL;
    }

    board.doMove(&curr, side);

    return new Move(curr.getX(), curr.getY());
}
