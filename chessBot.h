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

    int evaluate(const Board &board) const;

    pair<int, Move> minimax(Board board, int depth, Color turn);
private:
    vector<int> squareWeights;

};


#endif //CHESS_CHESSBOT_H