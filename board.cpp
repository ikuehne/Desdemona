#include "board.h"

Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
    weights = NULL;
}


/**
 * Create a board with a heuristic neural net with weights
 * in the given file.
 */
Board::Board(int* weights) {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);

    this->weights = weights;

}

Board::~Board() {
}

Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    newBoard->weights = weights;
    return newBoard;
}

bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}
 
bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}

 
bool Board::isDone() {
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

bool Board::hasMoves(Side side) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (checkMove(&move, side)) return true;
        }
    }
    return false;
}

bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == NULL) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

void Board::doMove(Move *m, Side side) {
    // A NULL move means pass.
    if (m == NULL) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

int Board::countBlack() {
    return black.count();
}

int Board::countWhite() {
    return taken.count() - black.count();
}

void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}

int Board::assess(Side side, bool testingMinimax) {
    int score = 0;

    int mul = side == WHITE? 1: -1;

    score += REGULAR_MUL * mul * countWhite();
    score -= REGULAR_MUL * mul * countBlack();

    if (testingMinimax) return score;
    
    // Noah's neural network assessment algorithm
    // IN PROGRESS
    
    score = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (taken[i] && !black[i]) score += mul * weights[i];
        if (taken[i] && black[i]) score -= mul * weights[i];
    
    }

    // feed through hidden neurons
    for (int n = 0; n < HIDDEN_NODES; n++)
    {
        int activation = 0;
        for (int s = 0; s < BOARD_SIZE; s++)
        {
            int w = BOARD_SIZE + n * BOARD_SIZE + s;
            if (taken[s] && !black[s])
                activation += mul * weights[w];
            if (taken[s] && black[s])
                activation -= mul * weights[w];
        }
        // index of weight from nth hidden neuron to output
        int w = BOARD_SIZE + HIDDEN_NODES * BOARD_SIZE + n;
        score += activation * weights[w];
    }

    return score;

}

int Board::old_assess(Side side, bool testingMinimax) {
    int score = 0;
    int mul = side == WHITE? 1: -1;

    score += REGULAR_MUL * mul * countWhite();
    score -= REGULAR_MUL * mul * countBlack();

    if (testingMinimax) return score;

    
    // Matrix operations

    // Left side.
    for (int i = 0; i < 64; i += 8) {
        if (taken[i] && !black[i]) score += mul * (SIDE_MUL - REGULAR_MUL);
        if (taken[i] &&  black[i]) score -= mul * (SIDE_MUL - REGULAR_MUL);
    }

    // Right side.
    for (int i = 7; i < 64; i += 8) {
        if (taken[i] && !black[i]) score += mul * (SIDE_MUL - REGULAR_MUL);
        if (taken[i] &&  black[i]) score -= mul * (SIDE_MUL - REGULAR_MUL);
    }

    // Bottom.
    for (int i = 0; i < 8; i ++) {
        if (taken[i] && !black[i]) score += mul * (SIDE_MUL - REGULAR_MUL);
        if (taken[i] &&  black[i]) score -= mul * (SIDE_MUL - REGULAR_MUL);
    }

    // Top.
    for (int i = 56; i < 64; i ++) {
        if (taken[i] && !black[i]) score += mul * (SIDE_MUL - REGULAR_MUL);
        if (taken[i] &&  black[i]) score -= mul * (SIDE_MUL - REGULAR_MUL);
    }

    // Corners.
    if (taken[0 ] && !black[0 ]) score += (CORNER_MUL - SIDE_MUL) * mul;
    if (taken[0 ] &&  black[0 ]) score -= (CORNER_MUL - SIDE_MUL) * mul;
    if (taken[7 ] && !black[7 ]) score += (CORNER_MUL - SIDE_MUL) * mul;
    if (taken[7 ] &&  black[7 ]) score -= (CORNER_MUL - SIDE_MUL) * mul;
    if (taken[56] && !black[56]) score += (CORNER_MUL - SIDE_MUL) * mul;
    if (taken[56] &&  black[56]) score -= (CORNER_MUL - SIDE_MUL) * mul;
    if (taken[63] && !black[63]) score += (CORNER_MUL - SIDE_MUL) * mul;
    if (taken[63] &&  black[63]) score -= (CORNER_MUL - SIDE_MUL) * mul;

    return score;
}

vector<Move *> *Board::getLegals(Side side) {
    Move *curr = new Move(0, 0);
    vector<Move *> *result = new vector<Move *>;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            curr->x = x;
            curr->y = y;
            if (checkMove(curr, side)) result->push_back(new Move(x, y));
       }
    }

    return result;
}
