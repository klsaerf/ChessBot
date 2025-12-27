/* Chess --- boardFunctions.cpp
 * Author: Kaan Pide 
 * Date  : 18.11.2025
 */

#include "boardFunctions.h"
#include <iostream>

namespace HelperFunctions {
    // Returns color of piece
    Color getColor(const char piece) {
        if (piece == '0') return EMPTY;
        return islower(piece) ? WHITE : BLACK;
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
                        const Color piece_color, const int index, const int x, const int y) {
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

        const Color piece_color = getColor(board[index]);

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

        const Color piece_color = getColor(board[index]);

        for (int i = 1; i < 8; i++) {
            urFlag = canMove(board, moves, urFlag, piece_color, index, x + i, y + i);
            ulFlag = canMove(board, moves, ulFlag, piece_color, index, x - i, y + i);
            drFlag = canMove(board, moves, drFlag, piece_color, index, x + i, y - i);
            dlFlag = canMove(board, moves, dlFlag, piece_color, index, x - i, y - i);
        }
    }

    // Returns all available squares in the knight's directions
    void getKnightMoves(const Board &board, Moves &moves, const int index) {

        const int x = index % 8;
        const int y = index / 8;

        const Color piece_color = getColor(board[index]);

        canMove(board, moves, false, piece_color, index, x + 1, y + 2);
        canMove(board, moves, false, piece_color, index, x - 1, y + 2);

        canMove(board, moves, false, piece_color, index, x + 2, y + 1);
        canMove(board, moves, false, piece_color, index, x - 2, y + 1);

        canMove(board, moves, false, piece_color, index, x + 2, y - 1);
        canMove(board, moves, false, piece_color, index, x - 2, y - 1);

        canMove(board, moves, false, piece_color, index, x + 1, y - 2);
        canMove(board, moves, false, piece_color, index, x - 1, y - 2);
    }

    // Returns all available moves a pawn can make
    void getPawnMoves(const Board &board, Moves &moves, const int index) {
        const int x = index % 8;
        const int y = index / 8;

        const Color piece_color = getColor(board[index]);
        const Color opponent_color = piece_color == WHITE ? BLACK : WHITE;

        const int direction = piece_color == WHITE ? 1 : -1;

        // Check pawn movement without canMove as pawn is special
        // in the sense that if it can move it cannot capture
        // but if it can capture it cannot move to that square
        if (isInBounds(x, y + direction) && board[index + 8 * direction] == '0') {
            moves.emplace_back(index, index + 8 * direction);
        }

        if ((piece_color == WHITE && y == 1) || (piece_color == BLACK && y == 6)) {
            if (isInBounds(index + 16 * direction) && board[index + 8 * direction] == '0' && board[index + 16 * direction] == '0') {
                moves.emplace_back(index, index + 16 * direction);
            }
        }

        if (isInBounds(x + 1, y + direction) && getColor(board[index + 1 + 8 * direction]) == opponent_color) {
            moves.emplace_back(index, index + 1 + 8 * direction);
        }

        if (isInBounds(x - 1, y + direction) && getColor(board[index - 1 + 8 * direction]) == opponent_color) {
            moves.emplace_back(index, index - 1 + 8 * direction);
        }
    }

    // Returns all available moves for the king
    void getKingMoves(const Board &board, Moves &moves, const int index) {
        const int x = index % 8;
        const int y = index / 8;

        const Color piece_color = getColor(board[index]);

        for (int i = 0; i < 9; i++) {
            // King's own square
            // canMove function will fail even if this
            // check isn't inplace, but saves computation
            if (i == 4) continue;

            const int x_offset = i % 3 - 1;
            const int y_offset = i / 3 - 1;
            canMove(board, moves, false, piece_color, index, x + x_offset, y + y_offset);
        }
    }


    // Returns the available moves for a given piece
    // board is gameboard, moves is move vector to modify,
    // index is piece's square
    void getAvailableMoves(const Board& board, Moves& moves, const int index) {
        switch (tolower(board[index])) {
            case 'r':
                getStraightMoves(board, moves, index);
                break;
            case 'n':
                getKnightMoves(board, moves, index);
                break;
            case 'b':
                getDiagonalMoves(board, moves, index);
                break;
            case 'q':
                getStraightMoves(board, moves, index);
                getDiagonalMoves(board, moves, index);
                break;
            case 'k':
                getKingMoves(board, moves, index);
                break;
            case 'p':
                getPawnMoves(board, moves, index);
                break;
            default:
                break;
        }
    }

    // Attempts a promotion
    // Function is called from makeMove which has
    // the pawn check already
    void attemptPromotion(Board& board, const int start, const int end) {
        const int y = end / 8;

        const Color piece_color = getColor(board[start]);

        if ((piece_color == WHITE && y == 7) || (piece_color == BLACK && y == 0)) {
            board[start] = piece_color == WHITE ? 'q' : 'Q';
        }
    }

}

using namespace HelperFunctions;

namespace BoardFunctions {
    void printBoard(const Board &board) {
        for (int i = 7; i >= 0; i--) {
            cout << i + 1 << "  ";
            for (int j = 0; j < 8; j++) {
                cout << board[i * 8 + j] << " ";
            }
            cout << endl;
        }
        cout << "   ";
        for (char rank = 'a'; rank <= 'h'; rank++) {
            cout << rank <<  " ";
        }
        cout << endl << endl;
    }

    Color isGameOver(const Board& board) {
        // White king captured -> black win
        const auto foundWhiteKing =
            find(board.begin(),
            board.end(),
            'k');
        if (foundWhiteKing == board.end()) return BLACK;

        // Black king captured -> white win
        const auto foundBlackKing =
            find(board.begin(),
            board.end(),
            'K');
        if (foundBlackKing == board.end()) return WHITE;

        // Game still ongoing
        return EMPTY;
    }


    bool isLegalMove(const Board& board, const int start, const int end, const Color turn) {
        // It's not the player's color
        if (getColor(board[start]) != turn) return false;

        // Check if the piece can move to the target square
        // All the necessary checks are handled in canMove
        // inside the getAvailableMoves
        Moves availableMoves;
        getAvailableMoves(board, availableMoves, start);
        const auto foundMove =
            find(availableMoves.begin(),
            availableMoves.end(),
            pair(start, end));
        return foundMove != availableMoves.end();
    }

    void makeMove(Board &board, const int start, const int end) {
        if (tolower(board[start]) == 'p') attemptPromotion(board, start, end);
        board[end] = board[start];
        board[start] = '0';
    }

    void getAllAvailableMoves(const Board& board, Moves& moves, const Color turn) {
        for (int i = 0; i < 64; i++) {
            const char piece = board[i];
            if (piece == '0') continue;

            if (turn == getColor(piece)) getAvailableMoves(board, moves, i);
        }
    }


    void populateBoard(Board &board) {
        for (int i = 0; i < 64; i++) {
            // White pieces
            if (i == 0 || i == 7) {
                board.emplace_back('r');
            }
            else if (i == 1 || i == 6) {
                board.emplace_back('n');
            }
            else if (i == 2 || i == 5) {
                board.emplace_back('b');
            }
            else if (i == 3) {
                board.emplace_back('q');
            }
            else if (i == 4) {
                board.emplace_back('k');
            }
            else if (i >= 8 && i <= 15) {
                board.emplace_back('p');
            }

            // Black pieces
            else if (i >= 48 && i <= 55) {
                board.emplace_back('P');
            }
            else if (i == 56 || i == 63) {
                board.emplace_back('R');
            }
            else if (i == 57 || i == 62) {
                board.emplace_back('N');
            }
            else if (i == 58 || i == 61) {
                board.emplace_back('B');
            }
            else if (i == 59) {
                board.emplace_back('Q');
            }
            else if (i == 60) {
                board.emplace_back('K');
            }

            // Empty squares
            else {
                board.emplace_back('0');
            }
        }
    }

    string convertIndexToNotation(const int index) {
        // converting the index into notation chars
        char rank = (index % 8) + 'a';
        char row = (index / 8) + '1';
        return {rank, row};
    }

    int convertNotationToIndex(const string& notation) {
        if (notation[0] < 'a' || notation[0] > 'h') return -1;
        if (notation[1] < '1' || notation[1] > '8') return -1;

        // converting the char into correct indexing
        int rank = notation[0] - 'a';
        int row = notation[1] - '1';
        return row * 8 + rank;
    }
}