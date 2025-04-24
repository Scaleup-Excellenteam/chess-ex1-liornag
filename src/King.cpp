#include "King.h"
#include "Board.h"
#include <cmath>

// Constructor: initialize the king with its symbol ('K' or 'k')
King::King(char symbol) : symbol(symbol) {}

// Return the king's symbol (used to identify player/color)
char King::getSymbol() const {
    return symbol;
}

// Check if a king move is legal
bool King::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = std::abs(toX - fromX); // Horizontal distance
    int dy = std::abs(toY - fromY); // Vertical distance

    // King can only move 1 square in any direction
    if (dx <= 1 && dy <= 1) {
        // Get the destination piece
        Piece* dest = board.getPiece(toX, toY);
        // Move is legal if destination is empty or contains opponent's piece
        return dest == nullptr || dest->getSymbol() != this->getSymbol();
    }
    return false; // Any move larger than 1 square is illegal
}
