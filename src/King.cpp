#include "King.h"
#include "Board.h"
#include <cmath>

King::King(char symbol) : symbol(symbol) {}

char King::getSymbol() const {
    return symbol;
}

bool King::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = std::abs(toX - fromX);
    int dy = std::abs(toY - fromY);

    if (dx <= 1 && dy <= 1) {
        Piece* dest = board.getPiece(toX, toY);
        return dest == nullptr || dest->getSymbol() != this->getSymbol();
    }
    return false;
}
