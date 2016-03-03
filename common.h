#ifndef __COMMON_H__
#define __COMMON_H__

/**
 * @brief Labels a side of the Othello game.
 */
enum Side { 
    WHITE, BLACK
};

/**
 * @brief Keep track of a move on the Othello board.
 */
class Move {
   
public:
    
    /**
     * @brief The x-coordinate of the move.
     */
    int x;

    /**
     * @brief The y-coordinate of the move.
     */
    int y;

    /**
     * @brief Create a move on the board.
     *
     * @param x The x-coordinate of the move.
     * @param y The y-coordinate of the move.
     */
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
    }

    bool operator==(const Move &other) {
        return this->x == other.x && this->y == other.y;
    }
    
    /**
     * @brief Clean up after a `Move`.
     */
    ~Move() {}

    /**
     * @brief Access the x-coordinate of the move.
     */
    int getX() { return x; }

    /**
     * @brief Access the y-coordinate of the move.
     */
    int getY() { return y; }

    /**
     * @brief Set the x-coordinate of the move.
     */
    void setX(int x) { this->x = x; }

    /**
     * @brief Set the y-coordinate of the move.
     */
    void setY(int y) { this->y = y; }
};

#endif
