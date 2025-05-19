#include "Knight.h"
#include "Board.h"
#include "Move.h"
#include <cctype>

Knight::Knight(char symbol) : symbol(symbol) {}

char Knight::getSymbol() const {
    return symbol;
}

bool Knight::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = std::abs(toX - fromX);
    int dy = std::abs(toY - fromY);

    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
        return false;
    }

    Piece* dest = board.getPiece(toX, toY);
    return dest == nullptr || std::isupper(dest->getSymbol()) != std::isupper(symbol);
}

void Knight::fillLegalMoves(int fromX, int fromY, std::vector<std::shared_ptr<Move>>& legalMoves, const Board& board) const {
    if (fromX >= 2) {
        if (fromY > 0) {
            if (isMoveLegal(fromX, fromY, fromX - 2, fromY - 1, board)) {
                legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX - 2, fromY - 1));
            }
        }
        if (fromY < BOARD_SIZE - 1) {
            if (isMoveLegal(fromX, fromY, fromX - 2, fromY + 1, board)) {
                legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX - 2, fromY + 1));
            }
        }
    }
    if (fromY < BOARD_SIZE - 2) {
        if (fromX > 0) {
            if (isMoveLegal(fromX, fromY, fromX - 1, fromY + 2, board)) {
                legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX - 1, fromY + 2));
            }
        }
        if (fromX < BOARD_SIZE - 1) {
            if (isMoveLegal(fromX, fromY, fromX + 1, fromY + 2, board)) {
                legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX + 1, fromY + 2));
            }
        }
    }
    if (fromX < BOARD_SIZE - 2) {
        if (fromY < BOARD_SIZE - 1) {
            if (isMoveLegal(fromX, fromY, fromX + 2, fromY + 1, board)) {
                legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX + 2, fromY + 1));
            }
        }
        if (fromY > 0) {
            if (isMoveLegal(fromX, fromY, fromX + 2, fromY - 1, board)) {
                legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX + 2, fromY - 1));
            }
        }
    }
    if (fromY >= 2) {
        if (fromX > 0) {
            if (isMoveLegal(fromX, fromY, fromX - 1, fromY - 2, board)) {
                legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX - 1, fromY - 2));
            }
        }
        if (fromX < BOARD_SIZE - 1) {
            if (isMoveLegal(fromX, fromY, fromX + 1, fromY - 2, board)) {
                legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX + 1, fromY - 2));
            }
        }
    }
}

int Knight::getValue() const {
    return 3;
}

bool Knight::isThreatening(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = std::abs(toX - fromX);
    int dy = std::abs(toY - fromY);

    return ((dx == 2 && dy == 1) || (dx == 1 && dy == 2));
}
