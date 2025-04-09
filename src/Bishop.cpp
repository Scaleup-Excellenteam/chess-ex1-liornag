#include "Bishop.h"
#include "Board.h"
#include <cmath>

Bishop::Bishop(char symbol) : symbol(symbol) {}

char Bishop::getSymbol() const {
    return symbol;
}

bool Bishop::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = toX - fromX;
    int dy = toY - fromY;

    if (std::abs(dx) != std::abs(dy)) {
        return false;  // לא תזוזה באלכסון
    }

    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;

    int x = fromX + stepX;
    int y = fromY + stepY;

    while (x != toX && y != toY) {
        if (board.getPiece(x, y) != nullptr) {
            return false;  // יש כלי בדרך
        }
        x += stepX;
        y += stepY;
    }

    Piece* dest = board.getPiece(toX, toY);
    return dest == nullptr || isupper(dest->getSymbol()) != isupper(symbol);
}
