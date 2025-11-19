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

    populateBoard(board);

    string input;
    while (true) {
        printBoard(board);

        cout << endl << "Enter the coordinates of your move (q for exit): ";
        getline(cin, input);
        if (input == "q" || input == "Q") {
            break;
        }

        const int start = (input[0] - '0') * 8 + (input[1] - '0');
        const int end = (input[2] - '0') * 8 + (input[3] - '0');
        if (isLegalMove(board, start, end)) makeMove(board, start, end);
        else cout << "Illegal move" << endl;
    }

    return 0;
}