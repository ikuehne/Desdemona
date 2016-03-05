#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include <vector>
#include "common.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#define REGULAR_MUL 1
#define SIDE_MUL 2
#define CORNER_MUL 3
#define BOARD_SIZE 64
#define TOTAL_WEIGHTS 584
#define HIDDEN_NODES 8

/**
 * @brief Encapsulate an Othello board.
 */
class Board {
 
private:

    /**
     * @brief All black pieces on the board.
     */
    bitset<64> black;

    /**
     * @brief All pieces of any color on the board.
     */
    bitset<64> taken;

    /**
     * @brief arrays storing weights for neural net heuristic.
     */
    int *weights;
 
    /**
     * @brief Check if a square is occupied.
     *
     * @param x The x-coordinate of the square to check.
     * @param y The y-coordinate of the square to check.
     *
     * @return Whether the square is occupied by a piece of either color.
     */
    bool occupied(int x, int y);

    /**
     * @brief Check if a piece of the given side is at the given square.
     *
     * Returns `false` if the square is empty or occupied by a piece of the
     * other color.
     *
     * @param side The side to check.
     * @param x The x-coordinate of the square to check.
     * @param y The y-coordinate of the square to check.
     *
     * @return Whether the given square is occupied by a piece of the given
     *         side.
     */
    bool get(Side side, int x, int y);

    /**
     * @brief Place a piece of the given side at the square.
     *
     * Does not check if the move is legal or even if the square is already
     * occupied.
     *
     * @param side The color of the piece to place.
     * @param x The x-coordinate of the square to place it at.
     * @param y The y-coordinate of the square to place it at.
     */
    void set(Side side, int x, int y);

    /**
     * @brief Return whether the given coordinate represents a valid square.
     *
     * @param x The x-coordinate to check.
     * @param y The y-coordinate to check.
     *
     * @return Whether both coordinates fall in the interval [0, 7].
     */
    bool onBoard(int x, int y);
      
public:

    /**
     * @brief Construct a new board in the usual starting position.
     */
    Board();

    /**
     * @brief board constructor that takes pointers to neural
     * network weights.
     */
    Board(int* weights);

    /**
     * @brief Clean up all resources associated with the board.
     */
    ~Board();

    /**
     * @brief Return a pointer to a copy of the board.
     *
     * @return A pointer to a newly allocated board with the same pieces.
     */
    Board *copy();
 
    /**
     * @brief Return whether the game is done. 
     *
     * @return `true` iff neither player has a valid move.
     */
    bool isDone();

    /**
     * @brief Return whether the given side has a valid move.
     *
     * @param side The side to check.
     *
     * @return `false` iff there is no valid move for `side`.
     */
    bool hasMoves(Side side);

    /**
     * @brief Check whether the given move is legal.
     *
     * @param m A pointer to the move to check.
     * @param side The side that would be making the move.
     *
     * @return `true` iff `side` can make `move` according to the rules of the
     *         game.
     */
    bool checkMove(Move *m, Side side);

    /**
     * @brief Make a move on the board.
     *
     * @param m A pointer to the move to make.
     * @param side The side that makes the move.
     */
    void doMove(Move *m, Side side);

    /**
     * @brief Count the number of pieces the given side has on the board.
     *
     * @param side The side to check for.
     *
     * @return The number of pieces that side has on the board.
     */
    int count(Side side);

    /**
     * @brief Return the number of black pieces on the board.
     *
     * @return The number of black pieces on the board.
     */
    int countBlack();

    /**
     * @brief Return the number of white pieces on the board.
     *
     * @return The number of white pieces on the board.
     */
    int countWhite();

    /**
     * @brief Set the board from a char array.
     *
     * `'w'` represents white pieces and `'b'` black pieces. Behavior for
     * other pieces is not specified.
     *
     * @param data A string to get the board from.
     */
    void setBoard(char data[]);


    int assess(Side side, bool testingMinimax);
    /**
     * @brief Provide an assessment of the favorability of the board.
     *
     * @param side The side to return an assessment for.
     *
     * @param testingMinimax Whether the minimax test is being run.  If it is,
     *                       a simpler heuristic function will be used.
     *
     * @return An integer score which is higher for a favorable position and
     *         lower for an unfavorable one.
     */
    int old_assess(Side side, bool testingMinimax);

    /**
     * @brief Get a vector of all legal moves for a given side.
     *
     * @param side The side making the move
     *
     * @return A vector of pointers to all legal moves for that side.
     */
    vector<Move *> *getLegals(Side side);
};

#endif
