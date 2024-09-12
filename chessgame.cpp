#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

void displayBoard(const int board[8][8]);
void getPieceInput(int& trueRow, int& trueColumn);
void displayPiece(int piece);
string getSquareNotation(int trueRow, int trueColumn);
void canMove(int piece, int trueRow, int trueColumn, const int board[8][8], vector<string>& moves);
bool move(int startRow, int startCol, int endRow, int endCol, int board[8][8]);


int main()
{
    int board[8][8] = {
        {1, 2, 3, 4, 5, 3, 2, 1},
        {9, 9, 9, 9, 9, 9, 9, 9},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {9, 9, 9, 9, 9, 9, 9, 9},
        {1, 2, 3, 4, 5, 3, 2, 1},
    };

    while (true) {
        displayBoard(board);

        int trueRow, trueColumn;
        getPieceInput(trueRow, trueColumn);

        if (trueRow == -1 && trueColumn == -1) {
            cout << "Exiting the program." << endl;
            break;
        }

        int piece = board[trueRow][trueColumn];
        if (piece == 0) {
            cout << "No piece at the selected square." << endl;
            continue;
        }


        cout << "Piece at " << getSquareNotation(trueRow, trueColumn) << ": ";
        displayPiece(piece);
        cout << endl;

        vector<string> moves;
        canMove(piece, trueRow, trueColumn, board, moves);

        if (moves.empty()) {
            cout << "No possible moves for this piece." << endl;
            continue;
        }

        string moveInput;
        while (true) {
            cout << "Enter the destination square (ex: e4): ";
            getline(cin, moveInput);

            if (find(moves.begin(), moves.end(), moveInput) == moves.end()) {
                cout << "Invalid move. Please enter a valid move." << endl;
                continue;
            }

            int endRow = 8 - (moveInput[1] - '0');
            int endCol = moveInput[0] - 'a';

            if (move(trueRow, trueColumn, endRow, endCol, board)) {
                break;
            }
            else {
                cout << "Failed to move the piece." << endl;
            }
        }
    }

    return 0;
}



void displayBoard(const int board[8][8])
{
    for (int i = 0; i < 8; i++) {
        cout << " ";
        for (int j = 0; j < 8; j++) {
            displayPiece(board[i][j]);
            if (j != 7) cout << " ";
        }
        cout << " " << endl;
    }
}

void getPieceInput(int& trueRow, int& trueColumn)
{
    string input;
    char column;
    int row;

    while (true) {
        cout << "Please enter a square (ex: e4) or 'q' to quit: ";
        getline(cin, input);

        if (input == "q" || input == "Q") {
            trueRow = -1;
            trueColumn = -1;
            return;
        }

        if (input.length() != 2) {
            cout << "Please enter a letter followed by a number (ex: e4)." << endl;
            continue;
        }

        column = tolower(input[0]);
        if (column < 'a' || column > 'h') {
            cout << "Invalid column. Please use letters a-h." << endl;
            continue;
        }

        if (!isdigit(input[1])) {
            cout << "Please use numbers from 1 to 8." << endl;
            continue;
        }

        row = input[1] - '0';
        if (row < 1 || row > 8) {
            cout << "Please use numbers from 1 to 8." << endl;
            continue;
        }

        trueColumn = column - 'a';
        trueRow = 8 - row;
        break;
    }
}


void displayPiece(int piece)
{
    switch (piece) {
    case 0: cout << "0"; break; // Case Vide
    case 1: cout << "T"; break; // Tour
    case 2: cout << "C"; break; // cavalier
    case 3: cout << "F"; break; // Fou
    case 4: cout << "D"; break; // Reine
    case 5: cout << "R"; break; // Roi
    case 9: cout << "P"; break; // Pion
    }
}

string getSquareNotation(int trueRow, int trueColumn)
{
    char column = 'a' + trueColumn;
    int row = 8 - trueRow;
    return string(1, column) + to_string(row);
}

void canMove(int piece, int trueRow, int trueColumn, const int board[8][8], vector<string>& moves)
{
    moves.clear();
    bool isBlackPawn = (piece == 9 && trueRow == 1); // Black pawn
    bool isWhitePawn = (piece == 9 && trueRow == 6); // White pawn

    if (piece == 9) { // Pawn
        if (isWhitePawn) {
            // White pawn moves
            if (trueRow > 0 && board[trueRow - 1][trueColumn] == 0) {
                moves.push_back(getSquareNotation(trueRow - 1, trueColumn));
                if (trueRow == 6 && board[trueRow - 2][trueColumn] == 0) {
                    moves.push_back(getSquareNotation(trueRow - 2, trueColumn));
                }
            }
            if (trueRow > 0) {
                if (trueColumn > 0 && board[trueRow - 1][trueColumn - 1] != 0) {
                    moves.push_back(getSquareNotation(trueRow - 1, trueColumn - 1));
                }
                if (trueColumn < 7 && board[trueRow - 1][trueColumn + 1] != 0) {
                    moves.push_back(getSquareNotation(trueRow - 1, trueColumn + 1));
                }
            }
        }
        else if (isBlackPawn) {
            // Black pawn moves
            if (trueRow < 7 && board[trueRow + 1][trueColumn] == 0) {
                moves.push_back(getSquareNotation(trueRow + 1, trueColumn));
                if (trueRow == 1 && board[trueRow + 2][trueColumn] == 0) {
                    moves.push_back(getSquareNotation(trueRow + 2, trueColumn));
                }
            }
            if (trueRow < 7) {
                if (trueColumn > 0 && board[trueRow + 1][trueColumn - 1] != 0) {
                    moves.push_back(getSquareNotation(trueRow + 1, trueColumn - 1));
                }
                if (trueColumn < 7 && board[trueRow + 1][trueColumn + 1] != 0) {
                    moves.push_back(getSquareNotation(trueRow + 1, trueColumn + 1));
                }
            }
        }
    }
    else if (piece == 1) { // Rook
        for (int i = 1; i < 8; i++) {
            if (trueRow + i < 8) { // Down
                if (board[trueRow + i][trueColumn] == 0) {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn));
                    break;
                }
            }
            if (trueRow - i >= 0) { // Up
                if (board[trueRow - i][trueColumn] == 0) {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn));
                    break;
                }
            }
            if (trueColumn + i < 8) { // Right
                if (board[trueRow][trueColumn + i] == 0) {
                    moves.push_back(getSquareNotation(trueRow, trueColumn + i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow, trueColumn + i));
                    break;
                }
            }
            if (trueColumn - i >= 0) { // Left
                if (board[trueRow][trueColumn - i] == 0) {
                    moves.push_back(getSquareNotation(trueRow, trueColumn - i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow, trueColumn - i));
                    break;
                }
            }
        }
    }
    else if (piece == 2) { // Knight
        int knightMoves[8][2] = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };
        for (auto& move : knightMoves) {
            int newRow = trueRow + move[0];
            int newCol = trueColumn + move[1];
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                if (board[newRow][newCol] == 0 || board[newRow][newCol] != piece) {
                    moves.push_back(getSquareNotation(newRow, newCol));
                }
            }
        }
    }
    else if (piece == 3) { // Bishop
        for (int i = 1; i < 8; i++) {
            if (trueRow + i < 8 && trueColumn + i < 8) {
                if (board[trueRow + i][trueColumn + i] == 0) {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn + i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn + i));
                    break;
                }
            }
            if (trueRow + i < 8 && trueColumn - i >= 0) {
                if (board[trueRow + i][trueColumn - i] == 0) {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn - i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn - i));
                    break;
                }
            }
            if (trueRow - i >= 0 && trueColumn + i < 8) {
                if (board[trueRow - i][trueColumn + i] == 0) {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn + i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn + i));
                    break;
                }
            }
            if (trueRow - i >= 0 && trueColumn - i >= 0) {
                if (board[trueRow - i][trueColumn - i] == 0) {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn - i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn - i));
                    break;
                }
            }
        }
    }
    else if (piece == 4) { // Queen
        // Rook moves
        for (int i = 1; i < 8; i++) {
            if (trueRow + i < 8) {
                if (board[trueRow + i][trueColumn] == 0) {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn));
                    break;
                }
            }
            if (trueRow - i >= 0) {
                if (board[trueRow - i][trueColumn] == 0) {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn));
                    break;
                }
            }
            if (trueColumn + i < 8) {
                if (board[trueRow][trueColumn + i] == 0) {
                    moves.push_back(getSquareNotation(trueRow, trueColumn + i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow, trueColumn + i));
                    break;
                }
            }
            if (trueColumn - i >= 0) {
                if (board[trueRow][trueColumn - i] == 0) {
                    moves.push_back(getSquareNotation(trueRow, trueColumn - i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow, trueColumn - i));
                    break;
                }
            }
        }
        // Bishop moves
        for (int i = 1; i < 8; i++) {
            if (trueRow + i < 8 && trueColumn + i < 8) {
                if (board[trueRow + i][trueColumn + i] == 0) {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn + i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn + i));
                    break;
                }
            }
            if (trueRow + i < 8 && trueColumn - i >= 0) {
                if (board[trueRow + i][trueColumn - i] == 0) {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn - i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow + i, trueColumn - i));
                    break;
                }
            }
            if (trueRow - i >= 0 && trueColumn + i < 8) {
                if (board[trueRow - i][trueColumn + i] == 0) {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn + i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn + i));
                    break;
                }
            }
            if (trueRow - i >= 0 && trueColumn - i >= 0) {
                if (board[trueRow - i][trueColumn - i] == 0) {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn - i));
                }
                else {
                    moves.push_back(getSquareNotation(trueRow - i, trueColumn - i));
                    break;
                }
            }
        }
    }
    else if (piece == 5) { // King
        int kingMoves[8][2] = {
            {1, 0}, {0, 1}, {-1, 0}, {0, -1},
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };
        for (auto& move : kingMoves) {
            int newRow = trueRow + move[0];
            int newCol = trueColumn + move[1];
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                if (board[newRow][newCol] == 0 || board[newRow][newCol] != piece) {
                    moves.push_back(getSquareNotation(newRow, newCol));
                }
            }
        }
    }
}



bool move(int startRow, int startCol, int endRow, int endCol, int board[8][8])
{
    if (endRow < 0 || endRow >= 8 || endCol < 0 || endCol >= 8) {
        return false; 
    }

    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = 0; 

    return true;
}

