// Chess
#include "../include/Chess.h"
#include "Board.h"
#include <iostream>
using namespace std;

int main()
{
    std::string boardStr = "###########################q#######R#######K####################";
    //string boardStr = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    //string boardStr = "##########K###############################R#############r#r#####";
    Chess a(boardStr);




    Board board(boardStr);
    int codeResponse = 0;
    int currentPlayer = 1;
    string res = a.getInput();



   while (res != "exit")
    {
       string move = res;  // Save the input move string (e.g. "e2e4")

        if (move.length() != 4) {
            codeResponse = 21; // Invalid move format, must be exactly 4 characters
        } else {
            // Convert chess notation (e.g. "e2") to board coordinates
            int fromX = move[0] - 'a'; // Column: 'a'-'h' → 0-7
            int fromY = move[1] - '1'; // Row: '1'-'8' → 0-7 (bottom to top)
            int toX   = move[2] - 'a';
            int toY   = move[3] - '1';

            // Debug print to show the move and coordinates
            cout << "DEBUG: move = " << move << endl;
            cout << "DEBUG: fromX = " << fromX << ", fromY = " << fromY << endl;
            cout << "DEBUG: toX   = " << toX << ", toY   = " << toY << endl;

            // Get the piece from the source square
            Piece* piece = board.getPiece(fromX, fromY);

            if (!piece) {
                // No piece at the source location
                cout << "DEBUG: No piece found at (" << fromX << "," << fromY << ")" << endl;
                codeResponse = 11;
            }
            // Check if the piece belongs to the opponent
            else if ((currentPlayer == 1 && islower(piece->getSymbol())) ||
                     (currentPlayer == 2 && isupper(piece->getSymbol()))) {
                codeResponse = 12;
            }
            else {
                // Check if destination square contains a piece of the same player
                Piece* dest = board.getPiece(toX, toY);
                if (dest &&
                    ((isupper(dest->getSymbol()) && isupper(piece->getSymbol())) ||
                     (islower(dest->getSymbol()) && islower(piece->getSymbol())))) {
                    codeResponse = 13; // Illegal move: destination has your own piece
                }
                // Check if the move is illegal for that specific piece
                else if (!piece->isMoveLegal(fromX, fromY, toX, toY, board)) {
                    codeResponse = 21; // Illegal move by that piece type
                }
                else {
                    // Create a temporary copy of the board to simulate the move
                    Board tempBoard = board; // העתק זמני של הלוח
                    tempBoard.movePiece(fromX, fromY, toX, toY);

                    // Check if the move would put the current player's king in check
                    if (tempBoard.isInCheck(currentPlayer == 1)) {
                        codeResponse = 31; // Move causes self-check — not allowed
                    } else {
                        // Move is legal and doesn't cause check → make it
                        board.movePiece(fromX, fromY, toX, toY);
                        codeResponse = 42;  // Move successful
                        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Switch turn
                    }
                }
            }
        }

        a.setCodeResponse(codeResponse);
        res = a.getInput();
    }

    cout << endl << "Exiting " << endl;
    return 0;
}
