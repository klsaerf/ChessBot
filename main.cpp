/* Chess --- main.cpp
 * Author: Kaan Pide
 * Date  : 18.11.2025
 */

#include <iostream>
#include "boardFunctions.h"
#include "chessBot.h"
#include <chrono>


using namespace std;
using namespace BoardFunctions;
using namespace std::chrono;

int main() {
    Board board;
    board.reserve(64);
    populateBoard(board);

    Color turn = WHITE;

    ChessBot chessBot;

    string input;
    while (true) {


        printBoard(board);
        const Color gameStatus = isGameOver(board);
        if (gameStatus != EMPTY) {
            cout << (gameStatus == WHITE ? "White" : "Black")  << " won!" << endl;
            break;
        }

        cout << "It's " << (turn == WHITE ? "white" : "black")  << "'s turn now." << endl;
        cout << "Enter the coordinates of your move (q for exit): ";
        getline(cin, input);
        if (input == "q" || input == "Q") {
            break;
        }

        const int start = (input[0] - '0') * 8 + (input[1] - '0');
        const int end = (input[2] - '0') * 8 + (input[3] - '0');

        if (isLegalMove(board, start, end, turn)) {
            makeMove(board, start, end);
            turn = turn == WHITE ? BLACK : WHITE;
        } else {
            cout << "Illegal move" << endl;
            continue;
        }

        auto s = high_resolution_clock::now();
        auto move = chessBot.minimax(board, 5, turn);
        auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - s);
        cout << duration.count() << " ms to think" << endl;

        makeMove(board, move.second.first, move.second.second);
        turn = turn == WHITE ? BLACK : WHITE;

        cout << endl << endl;
    }


    return 0;
}