#include "Board.h"

#include <iostream>

#include "Rook.h"
#include "King.h"
#include "Bishop.h"

Board::Board(const std::string& layout) {
    board.resize(8, std::vector<std::shared_ptr<Piece>>(8, nullptr));

    for (int i = 0; i < 64 && i < layout.length(); ++i) {
        char c = layout[i];
        int row =i / 8;  // ← הפוך את השורות
        int col = i % 8;

        std::cout << "DEBUG: Placing " << c << " at board[" << row << "][" << col << "]" << std::endl;

        switch (c) {
            case 'R':board[row][col] = std::make_shared<Rook>('R');
            break;
            case 'r':board[row][col] = std::make_shared<Rook>('r');
            break;
            case 'K':board[row][col] = std::make_shared<King>('K');
            break;
            case 'k':board[row][col] = std::make_shared<King>('k');
            break;
            case 'B': board[row][col] = std::make_shared<Bishop>('B');
            break;
            case 'b': board[row][col] = std::make_shared<Bishop>('b');
            break;

            default:
                board[row][col] = nullptr;
        }
    }
}

Piece* Board::getPiece(int x, int y) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
        return nullptr;
    return board[x][y].get();
}


void Board::movePiece(int fromX, int fromY, int toX, int toY) {
    board[toX][toY] = board[fromX][fromY];
    board[fromX][fromY] = nullptr;
}

bool Board::isInCheck(bool isWhite) const {
    char kingSymbol = isWhite ? 'K' : 'k';

    int kingX = -1, kingY = -1;

    // מוצאים את המלך
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* p = getPiece(x, y);
            if (p && p->getSymbol() == kingSymbol) {
                kingX = x;
                kingY = y;
                break;
            }
        }
    }

    if (kingX == -1) return false; // לא נמצא מלך (לא אמור לקרות)

    // עוברים על כל הכלים של היריב
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* p = getPiece(x, y);
            if (p && isupper(p->getSymbol()) != isWhite) {
                if (p->isMoveLegal(x, y, kingX, kingY, *this)) {
                    return true; // כלי יריב יכול לאיים על המלך
                }
            }
        }
    }

    return false;
}
