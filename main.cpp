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

// Helper function for splitting a string with a delimiter
vector<string> split(const string& str, const char delimiter) {
    vector<string> result;
    string tmp = str;

    while(tmp.find(delimiter) != string::npos) {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(!word.empty()) {
            result.push_back(word);
        }

    }
    if(!tmp.empty()) {
        result.push_back(tmp);
    }
    return result;
}


// Main loop of the game
bool mainLoop() {
    // Getting the users color
    cout << "What color would you like to play with (w/b, q for quit): ";
    string player_color;
    getline(cin, player_color);
    while (player_color != "w" && player_color != "b") {
        if (player_color == "q") return false;

        cout << "Please enter a valid color (w/b, q for quit): ";
        getline(cin, player_color);
    }
    Color turn = player_color == "w" ? WHITE : BLACK;

    // Getting the bots depth
    string bot_depth;
    int depth;
    cout << "Enter depth for the bot (an even integer recommended): ";
    while (true) {
        getline(cin, bot_depth);
        try {
            depth = stoi(bot_depth);
        } catch (invalid_argument const& _) {
            cout << "Please enter an integer: ";
            continue;
        }
        if (depth <= 0) {
            cout << "Please enter a non-negative integer: ";
            continue;
        }
        break;
    }

    // Setting the board and bot
    Board board;
    board.reserve(64);
    populateBoard(board);

    ChessBot chessBot;

    // Make the first move for black
    if (turn == BLACK) {
        auto [_, move] = chessBot.minimax(board, depth, WHITE);
        makeMove(board, move.first, move.second);
        cout << "The bot started with " << convertIndexToNotation(move.first)
        << " to " << convertIndexToNotation(move.second) << endl;
    }

    // The main game loop
    string input;
    while (true) {
        printBoard(board);

        // If the game is over, break the loop
        const Color gameStatus = isGameOver(board);
        if (gameStatus != EMPTY) {
            cout << (gameStatus == WHITE ? "White" : "Black")  << " won!" << endl;
            break;
        }

        // Get the move from the player
        cout << "It's " << (turn == WHITE ? "white" : "black")  << "'s turn now." << endl;
        cout << "Enter the coordinates of your move (q for exit): ";
        getline(cin, input);
        if (input == "q" || input == "Q") {
            return false;
        }

        // Split the input into 2 coordinates
        auto player_move = split(input, ' ');
        if (player_move.size() != 2) {
            cout << "Please enter 2 valid coordinates" << endl;
            continue;
        }
        const int start = convertNotationToIndex(player_move[0]);
        const int end = convertNotationToIndex(player_move[1]);

        // Check if the move is legal, make the move if it is
        if (isLegalMove(board, start, end, turn)) {
            makeMove(board, start, end);
            turn = turn == WHITE ? BLACK : WHITE;
        } else {
            cout << "Illegal move" << endl;
            continue;
        }

        // The bots turn
        // Also counts the time in ms for how long the bot takes its time
        // and how many moves are analysed
        auto now = high_resolution_clock::now();
        auto [_, move] = chessBot.minimax(board, depth, turn);
        auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - now);
        cout << duration.count() << " ms to think" << endl;
        cout << chessBot.movesMade() << " moves analysed" << endl;

        // The bot couldn't find a move that's better than losing
        // This implies checkmate
        if (move == NO_MOVE) {
            cout << "The bot forfeits!" << endl;
            break;
        }

        // Print bots move and make the move
        cout << "The bot played " << convertIndexToNotation(move.first)
        << " to " << convertIndexToNotation(move.second) << endl;

        makeMove(board, move.first, move.second);
        turn = turn == WHITE ? BLACK : WHITE;

        cout << endl << endl;
    }

    // Ask the user for a rematch
    cout << "Would you like to play again? (y/n): ";
    getline(cin, input);
    if (input == "y" || input == "Y") {
        cout << endl << endl;
        return true;
    }
    return false;
}


int main() {
    cout << "Welcome to Chess!" << endl << endl;

    while (mainLoop()) {}

    return 0;
}