#include "Bishop.h"
#include "Board.h"
#include "Move.h"
#include <cmath> // For std::abs (absolute value)

// Constructor: stores the symbol of the piece ('B' for white, 'b' for black)
Bishop::Bishop(char symbol) : symbol(symbol) {}

// Returns the symbol of the piece (used to identify the piece type and player)
char Bishop::getSymbol() const {
    return symbol;
}

// Checks if the bishop move is legal
bool Bishop::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = toX - fromX; // Change in row
    int dy = toY - fromY; // Change in column

    // Bishop can only move diagonally → absolute dx must equal absolute dy
    if (std::abs(dx) != std::abs(dy)) {
        return false;  // Not a diagonal move → illegal
    }

    // Determine the step direction in both axes
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;

    int x = fromX + stepX;
    int y = fromY + stepY;

    // Check all squares between source and destination (exclusive)
    while (x != toX && y != toY) {
        if (board.getPiece(x, y) != nullptr) {
            return false;  // יש כלי בדרך
        }
        x += stepX;
        y += stepY;
    }

    // Destination is valid if it's empty or contains opponent's piece
    Piece* dest = board.getPiece(toX, toY);
    return dest == nullptr || isupper(dest->getSymbol()) != isupper(symbol);
    // The pieces are from opposite players if their symbol cases differ (upper vs. lower)
}

void Bishop::fillLegalMoves(int fromX, int fromY, std::vector<std::shared_ptr<Move>>& legalMoves, const Board& board) const {
    for (int i = 1; i < fromX; i++) {
        if ((fromY - i > 0) && isMoveLegal(fromX, fromY, fromX - i, fromY - i, board)) {
            legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX - i, fromY - i));
        }
        if ((fromY + i < BOARD_SIZE) && isMoveLegal(fromX, fromY, fromX - i, fromY + i, board)) {
            legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX - i, fromY + i));
        }
    }
    for (int i = 1; i < BOARD_SIZE - fromX; i++) {
        if ((fromY - i > 0) && isMoveLegal(fromX, fromY, fromX + i, fromY - i, board)) {
            legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX + i, fromY - i));
        }
        if ((fromY + i < BOARD_SIZE) && isMoveLegal(fromX, fromY, fromX + i, fromY + i, board)) {
            legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX + i, fromY + i));
        }
    }
}

int Bishop::getValue() const {
    return 3;
}

bool Bishop::isThreatening(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = toX - fromX; // Change in row
    int dy = toY - fromY; // Change in column

    // Bishop can only move diagonally → absolute dx must equal absolute dy
    return std::abs(dx) == std::abs(dy);
}
