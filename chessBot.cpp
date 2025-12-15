/* Chess --- chessBot.cpp
 * Author: Kaan Pide 
 * Date  : 24.11.2025
 */

#include "chessBot.h"
#include <iostream>

using namespace BoardFunctions;


Board makeMove_(Board board, const int start, const int end) {
    //if (tolower(board[start]) == 'p') attemptPromotion(board, start, end);
    board[end] = board[start];
    board[start] = '0';
    return board;
}


ChessBot::ChessBot() {
    moveCounter_ = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == 0 || j == 0 || i == 7 || j == 7) {
                squareWeights_.push_back(1);
                continue;
            }
            if (i == 1 || j == 1 || i == 6 || j == 6) {
                squareWeights_.push_back(2);
                continue;
            }
            if (i == 2 || j == 2 || i == 5 || j == 5) {
                squareWeights_.push_back(3);
                continue;
            }
            if (i == 3 || j == 3 || i == 4 || j == 4) {
                squareWeights_.push_back(4);
            }
        }
    }
}

int ChessBot::evaluate(const Board &board) const {
    // TODO: add different weights for different pieces
    const Color game_state = isGameOver(board);
    if (game_state != EMPTY) return game_state == WHITE ? 10000 : -10000;

    int evaluation = 0;
    for (int i = 0; i < 64; i++) {
        if (board[i] == '0') continue;
        const Color piece_color = islower(board[i]) ? WHITE : BLACK;
        int piece_value = 0;
        switch (tolower(board[i])) {
            case 'r':
                piece_value = 50;
                break;
            case 'n':
                piece_value = 30;
                break;
            case 'b':
                piece_value = 30;
                break;
            case 'q':
                piece_value = 90;
                break;
            case 'k':
                piece_value = 150;
                break;
            case 'p':
                piece_value = 10;
                break;
            default:
                break;
        }
        evaluation += piece_color == WHITE ? piece_value + squareWeights_[i] : -1 * (piece_value + squareWeights_[i]);
    }

    return evaluation;
}

int ChessBot::movesMade() {
    const int temp = moveCounter_;
    moveCounter_ = 0;
    return temp;
}

pair<int, Move> ChessBot::minimax(Board board, const int depth, const Color turn) {
    #pragma omp critical
    {
        moveCounter_++;
    }
    if (isGameOver(board) != EMPTY || depth == 0) {
        return {evaluate(board), {0, 0}};
    }

    pair<int, Move> best;
    Moves availableMoves;

    getAllAvailableMoves(board, availableMoves, turn);

    if (turn == WHITE) {
        best = {-10000, {0, 0}};

        int i;
        #pragma omp parallel for
        for (i = 0; i < availableMoves.size(); i++) {
            const Move move = availableMoves[i];
            const Board newBoard = makeMove_(board, move.first, move.second);
            const pair<int, Move> newBest = {minimax(newBoard, depth-1, BLACK).first, move};
            #pragma omp critical
            {
                if (newBest.first > best.first) {
                    best = newBest;
                }
            }
        }
    }

    if (turn == BLACK) {
        best = {10000, {0, 0}};

        int i;
        #pragma omp parallel for
        for (i = 0; i < availableMoves.size(); i++) {
            const Move move = availableMoves[i];
            const Board newBoard = makeMove_(board, move.first, move.second);
            const pair<int, Move> newBest = {minimax(newBoard, depth-1, WHITE).first, move};
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

