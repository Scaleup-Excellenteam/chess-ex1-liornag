#include "Rook.h"
#include "Board.h"


Rook::Rook(char symbol) : symbol(symbol) {}  // שומר את הסמל ('R' או 'r')

char Rook::getSymbol() const {
    return symbol;
}

bool Rook::isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const {
    // בדיקה אם נשארים באותה שורה או באותה עמודה
    if (fromX != toX && fromY != toY) {
        return false; // לא תנועה ישרה
    }

    // בדיקה אם יש כלים בדרך – נלך צעד צעד ונבדוק
    int stepX = (toX > fromX) ? 1 : (toX < fromX ? -1 : 0);
    int stepY = (toY > fromY) ? 1 : (toY < fromY ? -1 : 0);

    int x = fromX + stepX;
    int y = fromY + stepY;

    while (x != toX || y != toY) {
        if (board.getPiece(x, y) != nullptr) {
            return false; // יש כלי בדרך
        }
        x += stepX;
        y += stepY;
    }

    // מותר לאכול כלי יריב או לזוז למשבצת ריקה
    Piece* dest = board.getPiece(toX, toY);
    return dest == nullptr || dest->getSymbol() != this->getSymbol(); // בהנחה שכלים לבנים ואותיות שונות
}
