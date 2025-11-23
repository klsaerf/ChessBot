/* Chess --- boardFunctions.h
 * Author: Kaan Pide 
 * Date  : 18.11.2025
 */

#ifndef CHESS_BOARDFUNCTIONS_H
#define CHESS_BOARDFUNCTIONS_H

#include <vector>

using namespace std;
using Board = vector<char>;
using Moves = vector<pair<int, int>>;

enum Color {WHITE, BLACK, EMPTY};


// Namespace that holds functions that manipulate game board
namespace BoardFunctions {
    // Prints the board
    void printBoard(const Board& board);

    // Returns the winner color if the game is over
    // Game is over when opponent king is captured
    Color isGameOver(const Board& board);

    // Returns if a move is legal or not
    // start is the square of piece to move
    // end is the square where the piece will move
    bool isLegalMove(const Board& board, int start, int end, Color turn);

    // Makes a move
    void makeMove(Board& board, int start, int end);

    // Populates the board
    // Lowercase characters represent white,
    // uppercase characters represent black pieces
    // and literal '0' represents an empty square
    // r -> rook  | n -> knight | b -> bishop
    // q -> queen | k -> king   | p -> pawn
    void populateBoard(Board& board);
}


#endif //CHESS_BOARDFUNCTIONS_H