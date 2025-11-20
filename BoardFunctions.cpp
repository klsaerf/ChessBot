/* Chess --- boardFunctions.cpp
 * Author: Kaan Pide 
 * Date  : 18.11.2025
 */

#include "BoardFunctions.h"
#include <iostream>

namespace HelperFunctions {
    // Returns color of piece
    // true for white, false for black
    bool getColor(const char piece) {
        return islower(piece) ? true : false;
    }

    // Checks if given index is in bounds
    bool isInBounds(const int index) {
        return index >= 0 && index < 64;
    }

    // Checks if given xy coordinates are in bounds
    bool isInBounds(const int x, const int y) {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }

    // Checks if a piece can move in the given direction
    // Returns true if the pieces vision ends (either the edge
    // of the board or another piece is there), false if the piece
    // can see further.
    // board is the gameboard, moves is the available moves the piece
    // can make, flag governs whether to keep checking for squares
    // piece_color is piece's color, and xy are the coordinates of the
    // target square
    bool canMove(const Board &board, Moves &moves, const bool flag,
                        const bool piece_color, const int index, const int x, const int y) {
        const int target_index = y * 8 + x;

        if (!flag && isInBounds(x, y)) {
            if (board[target_index] == '0') {
                moves.emplace_back(index, target_index);
                return false;
            }
            if (getColor(board[target_index]) != piece_color) {
                moves.emplace_back(index, target_index);
                return true;
            }
            return true;
        }
        return true;
    }

    // Returns all available squares in the straight directions
    // Used for rook and queen movement
    void getStraightMoves(const Board &board, Moves &moves, const int index) {

        bool upFlag = false;
        bool downFlag = false;
        bool leftFlag = false;
        bool rightFlag = false;

        const int x = index % 8;
        const int y = index / 8;

        const bool piece_color = getColor(board[index]);

        for (int i = 1; i < 8; i++) {
            upFlag = canMove(board, moves, upFlag, piece_color, index, x, y + i);
            downFlag = canMove(board, moves, downFlag, piece_color, index, x, y - i);
            leftFlag = canMove(board, moves, leftFlag, piece_color, index, x - i, y);
            rightFlag = canMove(board, moves, rightFlag, piece_color, index, x + i, y);
        }
    }

    // Returns all available squares in the diagonal directions
    // Used for bishop and queen movement
    void getDiagonalMoves(const Board &board, Moves &moves, const int index) {

        bool urFlag = false;
        bool ulFlag = false;
        bool drFlag = false;
        bool dlFlag = false;

        const int x = index % 8;
        const int y = index / 8;

        const bool piece_color = getColor(board[index]);

        for (int i = 1; i < 8; i++) {
            urFlag = canMove(board, moves, urFlag, piece_color, index, x + i, y + i);
            ulFlag = canMove(board, moves, ulFlag, piece_color, index, x - i, y + i);
            drFlag = canMove(board, moves, drFlag, piece_color, index, x + i, y - i);
            dlFlag = canMove(board, moves, dlFlag, piece_color, index, x - i, y - i);
        }
    }

    // Returns all available squares in the knight's directions
    void getKnightMoves(const Board& board, Moves &moves, const int index) {

        const int x = index % 8;
        const int y = index / 8;

        const bool piece_color = getColor(board[index]);

        canMove(board, moves, false, piece_color, index, x + 1, y + 2);
        canMove(board, moves, false, piece_color, index, x - 1, y + 2);

        canMove(board, moves, false, piece_color, index, x + 2, y + 1);
        canMove(board, moves, false, piece_color, index, x - 2, y + 1);

        canMove(board, moves, false, piece_color, index, x + 2, y - 1);
        canMove(board, moves, false, piece_color, index, x - 2, y - 1);

        canMove(board, moves, false, piece_color, index, x + 1, y - 2);
        canMove(board, moves, false, piece_color, index, x - 1, y - 2);
    }

    /*
    // Returns the available moves for a given piece
    // board is gameboard, index is piece's square
    vector<int> getAvailableMoves(const Board& board, const int index) {
        vector<int> moves;
        switch (board[index]) {

        }
    }
    */
}

using namespace HelperFunctions;

namespace BoardFunctions {
    void printBoard(const Board &board) {
        for (int i = 0; i < 64; i++) {
            cout << board[i] << " ";
            if (i % 8 == 7) cout << endl;
        }
    }

    bool isLegalMove(const Board& board, const int start, const int end) {
        // bounds check and if start is the same as end check
        if (!isInBounds(start) || !isInBounds(end) || start == end) {
            return false;
        }

        // cannot move empty piece
        if (board[start] == '0') {
            return false;
        }

        // cannot take your own piece but white
        if (islower(board[start]) && islower(board[end])) {
            return false;
        }
        // cannot take your own piece but black
        if (isupper(board[start]) && isupper(board[end])) {
            return false;
        }

        /*
        // Check if the piece can actually move to the target square
        vector<int> availableMoves = getAvailableMoves(board, start);
        const auto foundMove = find(availableMoves.begin(), availableMoves.end(), end);
        return foundMove != availableMoves.end();
        */

        return true;
    }

    void makeMove(Board &board, int start, int end) {
        board[end] = board[start];
        board[start] = '0';
    }

    void populateBoard(Board &board) {
        for (int i = 0; i < 64; i++) {
            // White pieces
            if (i == 0 || i == 7) {
                board[i] = 'r';
            }
            else if (i == 1 || i == 6) {
                board[i] = 'n';
            }
            else if (i == 2 || i == 5) {
                board[i] = 'b';
            }
            else if (i == 3) {
                board[i] = 'q';
            }
            else if (i == 4) {
                board[i] = 'k';
            }
            else if (i >= 8 && i <= 15) {
                board[i] = 'p';
            }

            // Black pieces
            else if (i >= 48 && i <= 55) {
                board[i] = 'P';
            }
            else if (i == 56 || i == 63) {
                board[i] = 'R';
            }
            else if (i == 57 || i == 62) {
                board[i] = 'N';
            }
            else if (i == 58 || i == 61) {
                board[i] = 'B';
            }
            else if (i == 59) {
                board[i] = 'Q';
            }
            else if (i == 60) {
                board[i] = 'K';
            }

            // Empty squares
            else {
                board[i] = '0';
            }
        }
    }
}