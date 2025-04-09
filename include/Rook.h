
#ifndef ROOK_H
#define ROOK_H

#pragma once
#include "Piece.h"

class Rook : public Piece {
private:
    char symbol;  // כאן נשמור את 'R' או 'r'

public:
    Rook(char symbol);  // ← זה הבנאי שצריך
    char getSymbol() const override;
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif //ROOK_H