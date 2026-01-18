/* Chess --- boardFunctions.h
 * Author: Kaan Pide 
 * Date  : 18.11.2025
 */

#ifndef CHESS_BOARDFUNCTIONS_H
#define CHESS_BOARDFUNCTIONS_H

#include <vector>
#include <string>

using namespace std;
using Board = vector<char>;
using Move = pair<int, int>;
using Moves = vector<Move>;

enum Color {WHITE, BLACK, EMPTY};

const Move NO_MOVE = {-1, -1};


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

    // Returns all available moves of the colors turn
    void getAllAvailableMoves(const Board& board, Moves& moves, Color turn);

    // Populates the board
    // Lowercase characters represent white,
    // uppercase characters represent black pieces
    // and literal '0' represents an empty square
    // r -> rook  | n -> knight | b -> bishop
    // q -> queen | k -> king   | p -> pawn
    void populateBoard(Board& board);

    // Converts a given index to chess notation
    // Example -> 0 = a1, 12 = e2
    string convertIndexToNotation(int index);

    // Converts a given notation to index
    // Example -> a1 = 0, e2 = 12
    int convertNotationToIndex(const string& notation);
}


#endif //CHESS_BOARDFUNCTIONS_H