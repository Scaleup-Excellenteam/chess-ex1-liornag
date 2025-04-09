#pragma once

class Board; // קדימה הצהרה – כדי לא ליצור תלות מעגלית

class Piece {
public:
    // פונקציה שבודקת אם מהלך חוקי לפי סוג הכלי
    virtual bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const = 0;

    // מחזירה את הסימן של הכלי – למשל 'R' לצריח
    virtual char getSymbol() const = 0;

    // דסטרקטור וירטואלי חשוב!
    virtual ~Piece() = default;
};
