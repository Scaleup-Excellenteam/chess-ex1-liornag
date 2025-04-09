#include "Board.h"

#include <iostream>

#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"

// Constructor: builds the board from a 64-character layout string
Board::Board(const std::string& layout) {
    // Initialize 8x8 board with null pointers
    board.resize(8, std::vector<std::shared_ptr<Piece>>(8, nullptr));

    // Loop through the layout string and place pieces
    for (int i = 0; i < 64 && i < layout.length(); ++i) {
        char c = layout[i];
        int row = i / 8; // Row index (0–7 from top to bottom)
        int col = i % 8; // Column index (0–7 from left to right)


        // Switch to place correct piece depending on the character
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
            case 'Q': board[row][col] = std::make_shared<Queen>('Q');
            break;
            case 'q': board[row][col] = std::make_shared<Queen>('q');
            break;

            default:
                board[row][col] = nullptr; // Empty square or unsupported piece
        }
    }
}

// Returns a pointer to the piece at the given coordinates
Piece* Board::getPiece(int x, int y) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
        return nullptr;  // Out of bounds
    return board[x][y].get();
}

// Moves a piece from (fromX, fromY) to (toX, toY)
void Board::movePiece(int fromX, int fromY, int toX, int toY) {
    board[toX][toY] = board[fromX][fromY];   // Move the piece
    board[fromX][fromY] = nullptr;           // Empty the source square
}

// Checks if the king of the given player is currently in check
bool Board::isInCheck(bool isWhite) const {
    char kingSymbol = isWhite ? 'K' : 'k'; // Use correct symbol for the player's king

    int kingX = -1, kingY = -1;

    // First, locate the king on the board
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

    if (kingX == -1) return false; /// King not found

    // Now, check if any enemy piece can legally move to the king's position
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* p = getPiece(x, y);
            if (p && isupper(p->getSymbol()) != isWhite) { // Opponent's piece
                if (p->isMoveLegal(x, y, kingX, kingY, *this)) {
                    return true; // Enemy piece can attack the king → check
                }
            }
        }
    }

    return false; // No threats found → not in check
}
