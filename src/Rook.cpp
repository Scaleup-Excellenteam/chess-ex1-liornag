#include "Rook.h"
#include "Board.h"

// Constructor: sets the piece's symbol ('R' for white, 'r' for black)
Rook::Rook(char symbol) : symbol(symbol) {}

// Returns the piece's symbol
char Rook::getSymbol() const {
    return symbol;
}

// Checks if a rook move is legal
bool Rook::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
     // Rooks move only in straight lines (horizontal or vertical)
    if (fromX != toX && fromY != toY) {
        return false; // Not a straight-line move → illegal
    }

    // Determine step direction (row and column)
    int stepX = (toX > fromX) ? 1 : (toX < fromX ? -1 : 0); // 1, -1, or 0
    int stepY = (toY > fromY) ? 1 : (toY < fromY ? -1 : 0); // 1, -1, or 0

    int x = fromX + stepX;
    int y = fromY + stepY;

    // Check all squares between source and destination
    while (x != toX || y != toY) {
        if (board.getPiece(x, y) != nullptr) {
            return false; // There's a piece blocking the path
        }
        x += stepX;
        y += stepY;
    }

    // At destination: it's legal if the square is empty or has an opponent's piece
    Piece* dest = board.getPiece(toX, toY);
    return dest == nullptr || dest->getSymbol() != this->getSymbol();
}
