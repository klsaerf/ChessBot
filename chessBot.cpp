/* Chess --- chessBot.cpp
 * Author: Kaan Pide 
 * Date  : 24.11.2025
 */

#include "chessBot.h"

#include <algorithm>
#include <iostream>

using namespace BoardFunctions;

Color getColor(const char piece) {
    if (piece == '0') return EMPTY;
    return islower(piece) ? WHITE : BLACK;
}

void attemptPromotion(Board& board, const int start, const int end) {
    const int y = end / 8;

    const Color piece_color = getColor(board[start]);

    if ((piece_color == WHITE && y == 7) || (piece_color == BLACK && y == 0)) {
        board[start] = piece_color == WHITE ? 'q' : 'Q';
    }
}

Board makeMove_(Board board, const int start, const int end) {
    if (tolower(board[start]) == 'p') attemptPromotion(board, start, end);
    board[end] = board[start];
    board[start] = '0';
    return board;
}


ChessBot::ChessBot() {
    moveCounter_ = 0;
    pieceWeights_.reserve(64);
    kingWeights_.reserve(64);

    // A predefined weight for pawns
    // Center pawns are favored
    whitePawnWeights_ = {
        1, 2, 4, 5, 5, 4, 2, 1,
        2, 3, 5, 6, 6, 5, 3, 2,
        2, 3, 6, 7, 7, 6, 3, 2,
        3, 4, 7, 8, 8, 7, 4, 3,
        3, 4, 8, 9, 9, 8, 4, 3,
        4, 5, 9, 10, 10, 9, 5, 4,
        4, 5, 10, 11, 11, 10, 5, 4,
        5, 6, 11, 12, 12, 11, 6, 5,
    };

    // Black pawns are the same weights, but reversed
    blackPawnWeights_ = whitePawnWeights_;
    reverse(blackPawnWeights_.begin(), blackPawnWeights_.end());

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Pieces are stronger in the center
            // Kings are safer outside
            if (i == 0 || j == 0 || i == 7 || j == 7) {
                pieceWeights_.push_back(2);
                kingWeights_.push_back(8);
                continue;
            }
            if (i == 1 || j == 1 || i == 6 || j == 6) {
                pieceWeights_.push_back(4);
                kingWeights_.push_back(6);
                continue;
            }
            if (i == 2 || j == 2 || i == 5 || j == 5) {
                pieceWeights_.push_back(6);
                kingWeights_.push_back(4);
                continue;
            }
            if (i == 3 || j == 3 || i == 4 || j == 4) {
                pieceWeights_.push_back(8);
                kingWeights_.push_back(2);
            }
        }
    }
}

int ChessBot::evaluate(const Board &board) const {
    // Checkmate check
    const Color game_state = isGameOver(board);
    if (game_state != EMPTY) return game_state == WHITE ? 10000 : -10000;

    // Add the points for each piece with their according weights to evaluation
    // White pieces are added, black pieces are subtracted
    int evaluation = 0;
    for (int i = 0; i < 64; i++) {
        if (board[i] == '0') continue;
        const Color piece_color = islower(board[i]) ? WHITE : BLACK;
        int piece_value = 0;
        switch (tolower(board[i])) {
            case 'r':
                piece_value = 50 + pieceWeights_[i];
                break;
            case 'n':
                piece_value = 30 + pieceWeights_[i];
                break;
            case 'b':
                piece_value = 30 + pieceWeights_[i];
                break;
            case 'q':
                piece_value = 90 + pieceWeights_[i];
                break;
            case 'k':
                piece_value = 150 + kingWeights_[i];
                break;
            case 'p':
                piece_value = 10 + (piece_color == WHITE ? whitePawnWeights_[i] : blackPawnWeights_[i]);
                break;
            default:
                break;
        }
        evaluation += piece_color == WHITE ? piece_value : -1 * piece_value;
    }

    return evaluation;
}

int ChessBot::movesMade() {
    // Return the moves made and reset the counter
    const int temp = moveCounter_;
    moveCounter_ = 0;
    return temp;
}

pair<int, Move> ChessBot::minimax(Board board, const int depth, const Color turn) {
    // For counting the moves, negatively affects the performance
    // Can be removed if someone wants a faster algorithm
    #pragma omp critical
    {
        moveCounter_++;
    }

    // Base recursion case
    if (isGameOver(board) != EMPTY || depth == 0) {
        return {evaluate(board), NO_MOVE};
    }

    pair<int, Move> best;
    Moves availableMoves;

    // All the available moves for the given turn
    getAllAvailableMoves(board, availableMoves, turn);

    // The moves for all the moves are evaluated, and then the best performing move is made
    if (turn == WHITE) {
        best = {-10000, NO_MOVE};

        int i;

        #pragma omp parallel for default(none) firstprivate(depth, board) shared(best, availableMoves)
        for (i = 0; i < availableMoves.size(); i++) {
            const Move move = availableMoves[i];
            const Board newBoard = makeMove_(board, move.first, move.second);
            const pair<int, Move> newBest = {minimax(newBoard, depth - 1, BLACK).first, move};
            #pragma omp critical
            {
                if (newBest.first > best.first) {
                    best = newBest;
                }
            }
        }
    }

    if (turn == BLACK) {
        best = {10000, NO_MOVE};

        int i;

        #pragma omp parallel for default(none) firstprivate(depth, board) shared(best, availableMoves)
        for (i = 0; i < availableMoves.size(); i++) {
            const Move move = availableMoves[i];
            const Board newBoard = makeMove_(board, move.first, move.second);
            const pair<int, Move> newBest = {minimax(newBoard, depth - 1, WHITE).first, move};
            #pragma omp critical
            {
                if (newBest.first < best.first) {
                    best = newBest;
                }
            }
        }
    }
    return best;
}

