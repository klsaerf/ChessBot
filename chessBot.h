/* Chess --- chessBot.h
 * Author: Kaan Pide 
 * Date  : 24.11.2025
 */

#ifndef CHESS_CHESSBOT_H
#define CHESS_CHESSBOT_H

#include "boardFunctions.h"

using namespace std;

class ChessBot {
public:
    ChessBot();

    // Evaluates the board
    // Adds the pieces values based on their weights
    // White pieces are added, black pieces are subtracted
    int evaluate(const Board &board) const;

    // Counts how many moves are evaluated by the algorithm
    int movesMade();

    // The minimax algorithm
    // The algorithm will run for all possible moves until the
    // given depth has been reached, then the best possible
    // outcome is chosen and returned. Increasing the depth
    // exponentially slows the algorithm, due to how chess works.
    pair<int, Move> minimax(Board board, int depth, Color turn);
private:
    // Weights for different piece types
    // All the pieces require a different set of weights
    vector<int> pieceWeights_;
    vector<int> kingWeights_;
    vector<int> whitePawnWeights_;
    vector<int> blackPawnWeights_;

    // Counts the moves
    int moveCounter_;
};


#endif //CHESS_CHESSBOT_H