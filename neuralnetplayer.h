#ifndef __NET_PLAYER_H__
#define __NET_PLAYER_H__

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "common.h"
#include "board.h"

#define HIDDEN_NODES 8
#define TOTAL_WEIGHTS 584

/**
 * @brief represent an Othello player.
 *
 * The player also keeps track of its board.
 */
class NeuralNetPlayer {

public:


    /**
     * @brief creates a new player playing the given side
     * with neural network weights specified by a file.
     */
    NeuralNetPlayer(Side side, char* weightFile);

    /**
     * @brief Cleans up all resources allocated for the player.
     */
    ~NeuralNetPlayer();
    
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

private:

    /**
     * @brief arrays storing weights for neural net heuristic.
     */
    int weights[TOTAL_WEIGHTS];

    /**
     * @brief This player's side.
     */
    Side side;

    /**
     * @brief The other player's side.
     */
    Side opponent;

    /**
     * @brief The board of play.
     */
    Board board;

};

#endif
