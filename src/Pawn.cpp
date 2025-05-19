#include "Pawn.h"
#include "Board.h"
#include "Move.h"
#include <cctype>

Pawn::Pawn(char symbol) : symbol(symbol) {}

char Pawn::getSymbol() const {
    return symbol;
}

bool Pawn::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int direction = std::isupper(symbol) ? 1 : -1;           // לבן יורד, שחור עולה
    int startRow  = std::isupper(symbol) ? 1 : 6;            // שורת ההתחלה לפיון לבן/שחור

    int dx = toX - fromX;
    int dy = toY - fromY;

    Piece* dest = board.getPiece(toX, toY);

    // צעד רגיל קדימה
    if (dx == 0 && dy == direction && dest == nullptr) {
        return true;
    }

    // צעד כפול מהשורה הראשונה
    if (dx == 0 && dy == 2 * direction && fromY == startRow &&
        board.getPiece(fromX, fromY + direction) == nullptr && dest == nullptr) {
        return true;
        }

    // אכילה באלכסון
    if (dy == direction && std::abs(dx) == 1 && dest != nullptr &&
        std::isupper(dest->getSymbol()) != std::isupper(symbol)) {
        return true;
        }

    return false;
}

void Pawn::fillLegalMoves(int fromX, int fromY, std::vector<std::shared_ptr<Move>>& legalMoves, const Board& board) const {
    int direction = std::isupper(symbol) ? 1 : -1;           // לבן יורד, שחור עולה
    int startRow = std::isupper(symbol) ? 1 : 6;            // שורת ההתחלה לפיון לבן/שחור
    for (int i = 1; i <= 2; i++) {
        if (isMoveLegal(fromX, fromY, fromX, fromY + i * direction, board)) {
            legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX, fromY + i * direction));
        }
    }
    if (isMoveLegal(fromX, fromY, fromX + 1, fromY + direction, board)) {
        legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX + 1, fromY + direction));
    }
    if (isMoveLegal(fromX, fromY, fromX - 1, fromY + direction, board)) {
        legalMoves.push_back(std::make_shared<Move>(fromX, fromY, fromX - 1, fromY + direction));
    }
}

int Pawn::getValue() const {
    return 1;
}

bool Pawn::isThreatening(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int direction = std::isupper(symbol) ? 1 : -1;           // לבן יורד, שחור עולה
    int dx = toX - fromX;
    int dy = toY - fromY;
    return (std::abs(dx) == 1) && (dy == direction);
}
