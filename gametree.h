#include <utility>
#include <vector>
#include <iostream>
#include "common.h"
#include "board.h"
#include <cassert>

using namespace std;

class GameTree {
public:
    /**
     * @brief Create a game tree and populate it to a given level.
     *
     * @param board A pointer to the current board.
     * @param side The side to play for.
     * @param level The ply to create the game tree to.
     * @param testingMinimax Whether to use the simplified heuristic for
     *                       testing Minimax.
     *
     */
    GameTree(Board *board, Side side, int level, bool testingMinimax);

    /**
     * @brief Clean up any resources allocated by the game tree.
     */
    ~GameTree();

    /**
     * @brief Provide a score for the tree using the current depth.
     */
    int assess();

    /**
     * @brief Get the best move from the current position.
     */
    Move *getBestMove();

    /**
     * @brief Perform a move and await the response.
     */
    void doMove(Move *move);

    /**
     * @brief Perform the opponent's move and get up the next ply.
     */
    void doOpponentMove(Move *move);


protected:

    /**
     * @brief Create a game tree and populate it to a given level. Utility
     * constructor used to ensure every level knows what the original depth of
     * the tree was.
     *
     * @param board A pointer to the current board.
     * @param side The side to play for.
     * @param level The ply to create the game tree to.
     * @param originalLevel The level originally specified for the tree.
     * @param testingMinimax Whether to use the simplified heuristic for
     *                       testing Minimax.
     *
     */
    GameTree(Board *board, Side side, int level, int originalLevel, 
             bool testingMinimax);

    /**
     * @brief The original depth of the tree.
     */
    int startingdepth;

    /**
     * @brief Add new levels to the game tree.
     *
     * @param c The number of levels to add.
     */
    void addPly(int c);

    /**
     * @brief Keep track of all possible moves from this point and the
     *        resulting trees.
     *
     * NULL if this is the bottom of the tree.
     */
    vector<pair<Move *, GameTree *> > *next;

    /**
     * @brief The board at this point.
     */
    Board *board;

    /**
     * @brief The side of the player.
     */
    Side side;

    /**
     * @brief The best known move from this point, or NULL if the best move
     *        has not been calculated.
     */
    Move *best_move;

    /**
     * @brief The worst known score below this point, or NULL if that has not
     *        been calculated.
     */
    int *worst_score;

    /**
     * @brief Whether the tree is being used to test minimax.
     */
    bool testingMinimax;

    /**
     * @brief The original level of the tree.
     */
    int originalLevel;
};
