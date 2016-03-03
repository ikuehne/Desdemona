#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = Board();   
    this->side = side;
    opponent = side == BLACK? WHITE: BLACK;
    srand(time(NULL));
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
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
