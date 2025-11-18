/* Chess --- boardFunctions.cpp
 * Author: Kaan Pide 
 * Date  : 18.11.2025
 */

#include "BoardFunctions.h"
#include <iostream>

namespace HelperFunctions {
    // Returns 1 if the move is legal, 0 otherwise
    // Helper function in makeMove()
    bool _isLegalMove(const Board& board, const int start, const int end) {
        // bounds check and if start is the same as end check
        if (start > 63 || end > 63 || start == end || start < 0 || end < 0) {
            return false;
        }
        // cannot move empty piece
        if (board[start] == '0') {
            return false;
        }

        // cannot take your own piece but white
        if (board[start] > '[' && board[end] > '[') {
            return false;
        }
        // cannot take your own piece but black
        if (board[start] > '@' && board[end] > '@' && board[start] < '[' && board[end] < '[') {
            return false;
        }
        return true;
    }
}


namespace BoardFunctions {
    void printBoard(const Board &board) {
        for (int i = 0; i < 64; i++) {
            cout << board[i] << " ";
            if (i % 8 == 7) cout << endl;
        }
    }

    void makeMove(Board &board, int start, int end) {
        if (!HelperFunctions::_isLegalMove(board, start, end)) {
            cout << "Illegal move" << endl;
            return;
        }
        board[end] = board[start];
        board[start] = '0';
    }

    void populateBoard(Board &board) {
        for (int i = 0; i < 64; i++) {
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

            else {
                board[i] = '0';
            }
        }
    }
}