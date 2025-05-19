#include "Queen.h"
#include "Board.h"
#include "Move.h"
#include <cmath>

// Constructor: stores the symbol of the queen ('Q' or 'q')
Queen::Queen(char symbol) : symbol(symbol) {}

// Returns the symbol of the piece
char Queen::getSymbol() const {
    return symbol;
}

// Check if the queen's move is legal
bool Queen::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = toX - fromX; // Change in row
    int dy = toY - fromY; // Change in column

    // Queen moves like both a rook and a bishop:
    // valid if it's a straight line (dx == 0 or dy == 0) or a diagonal (|dx| == |dy|)
    if (dx == 0 || dy == 0 || std::abs(dx) == std::abs(dy)) {
        // Determine step direction for both axes
        int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
        int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

        int x = fromX + stepX;
        int y = fromY + stepY;

        // Check all squares between source and destination (exclusive)
        while (x != toX || y != toY) {
            if (board.getPiece(x, y) != nullptr) {
                return false;  // Path is blocked by another piece
            }
            x += stepX;
            y += stepY;
        }

        // At destination: allow if it's empty or has an opponent's piece
        Piece* dest = board.getPiece(toX, toY);
        return dest == nullptr || isupper(dest->getSymbol()) != isupper(symbol);
        // If one is uppercase and the other is lowercase, they are opponents
    }
    // Not a valid queen move (not straight and not diagonal)
    return false;
}

void Queen::fillLegalMoves(int fromX, int fromY, std::vector<std::shared_ptr<Move>>& legalMoves, const Board& board) const {
    for (int i = 0; i < fromX; i++) {
        if (isMoveLegal(fromX, fromY, i, fromY, board)) {
            legalMoves.push_back(std::make_shared<Move>(fromX, fromY, i, fromY));
        }
    }
    for (int i = fromX + 1; i < BOARD_SIZE; i++) {
        if (isMoveLegal(fromX, fromY, i, fromY, board)) {
            legalMoves.push_back(std::make_shared<Move>(fromX, fromY, i, fromY));
        }
    }
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

int Queen::getValue() const {
    return 9;
}

bool Queen::isThreatening(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = std::abs(toX - fromX); // Change in row
    int dy = std::abs(toY - fromY); // Change in column

    // Queen moves like both a rook and a bishop:
    // valid if it's a straight line (dx == 0 or dy == 0) or a diagonal (|dx| == |dy|)
    if ((dx == 0) && (dy > 0)) {
        return true;
    }
    if ((dy == 0) && (dx > 0)) {
        return true;
    }
    return dx == dy;
}
