// Chess
#include "../include/Chess.h"
#include "Board.h"
#include <iostream>
using namespace std;

int main()
{
    std::string boardStr = "#########B########R########K##############################r#####";
    Chess a(boardStr);


    Board board(boardStr);
    int codeResponse = 0;
    int currentPlayer = 1;
    string res = a.getInput();



   while (res != "exit")
    {
        string move = res;

        if (move.length() != 4) {
            codeResponse = 21;
        } else {
            int fromX = move[0] - 'a';         // a-h → 0-7 ← זה יהיה row
            int fromY = move[1] - '1';         // '1'-'8' → 0-7 ← זה יהיה col
            int toX   = move[2] - 'a';
            int toY   = move[3] - '1';

            cout << "DEBUG: move = " << move << endl;
            cout << "DEBUG: fromX = " << fromX << ", fromY = " << fromY << endl;
            cout << "DEBUG: toX   = " << toX << ", toY   = " << toY << endl;

            Piece* piece = board.getPiece(fromX, fromY);

            if (!piece) {
                cout << "DEBUG: No piece found at (" << fromX << "," << fromY << ")" << endl;
                codeResponse = 11;
            }
            else if ((currentPlayer == 1 && islower(piece->getSymbol())) ||
                     (currentPlayer == 2 && isupper(piece->getSymbol()))) {
                codeResponse = 12;
            }
            else {
                Piece* dest = board.getPiece(toX, toY);
                if (dest &&
                    ((isupper(dest->getSymbol()) && isupper(piece->getSymbol())) ||
                     (islower(dest->getSymbol()) && islower(piece->getSymbol())))) {
                    codeResponse = 13;
                }
                else if (!piece->isMoveLegal(fromX, fromY, toX, toY, board)) {
                    codeResponse = 21;
                }
                else {
                    Board tempBoard = board; // העתק זמני של הלוח
                    tempBoard.movePiece(fromX, fromY, toX, toY);

                    if (tempBoard.isInCheck(currentPlayer == 1)) {
                        codeResponse = 31; // תנועה גורמת לשח עצמי
                    } else {
                        board.movePiece(fromX, fromY, toX, toY);
                        codeResponse = 42;
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
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
