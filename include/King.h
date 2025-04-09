//
// Created by liorn on 09/04/2025.
//

#ifndef KING_H
#define KING_H
#pragma once
#include "Piece.h"

class King : public Piece {
private:
    char symbol;

public:
    King(char symbol);
    char getSymbol() const override;
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif //KING_H
