/* Chess --- main.cpp
 * Author: Kaan Pide
 * Date  : 18.11.2025
 */

#include <iostream>
#include "BoardFunctions.h"


using namespace std;
using namespace BoardFunctions;

int main() {
    Board board;
    board.reserve(64);

    Color turn = WHITE;

    populateBoard(board);

    string input;
    while (true) {
        printBoard(board);
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
        }

        else cout << "Illegal move" << endl;
        cout << endl << endl;
    }

    return 0;
}