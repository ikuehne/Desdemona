#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "common.h"
#include "board.h"
#include "gametree.h"

/**
 * @brief represent an Othello player.
 *
 * The player also keeps track of its board.
 */
class Player {

public:

    /**
     * @brief Creates a new player playing the given side.
     */
    Player(Side side);

    /**
     * @brief Cleans up all resources allocated for the player.
     */
    ~Player();
    
    /**
     * @brief Performs the opponent's move and returns this player's move.
     *
     * Keeps `board` consistent with both moves.
     *
     * @param opponentsMove A pointer to the opponent's last move.
     * @param msLeft The number of milliseconds allowed for this player, or -1
     *               if there is no limit.
     * 
     * @return A pointer to this player's next move, or NULL if no valid move
     *         is left.
     */
    Move *doMove(Move *opponentsMove, int msLeft);

    /**
     * @brief Flag to tell if the player is running within the test_minimax
     *        context
     */
    bool testingMinimax;

    /**
     * @brief The starting board.
     */
    Board *startingBoard;

private:

    /**
     * @brief This player's side.
     */
    Side side;

    /**
     * @brief The board of play.
     */
    GameTree *tree;
};

#endif
