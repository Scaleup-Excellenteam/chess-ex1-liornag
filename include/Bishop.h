//
// Created by liorn on 09/04/2025.
//

#ifndef BISHOP_H
#define BISHOP_H

#pragma once
#include "Piece.h"

class Bishop : public Piece {
private:
    char symbol;

public:
    Bishop(char symbol);
    char getSymbol() const override;
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif //BISHOP_H
