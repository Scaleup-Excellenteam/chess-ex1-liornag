//
// Created by liorn on 08/05/2025.
//

#ifndef KNIGHT_H
#define KNIGHT_H
#pragma once

#include "Piece.h"

class Knight : public Piece {
private:
    char symbol; // Stores the piece's symbol ('Q' or 'q'), used to identify the player

public:
    Knight(char symbol);
    char getSymbol() const override;
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override;
    virtual void fillLegalMoves(int fromX, int fromY, std::vector<std::shared_ptr<Move>>& legalMoves, const Board& board) const override;
    virtual bool isThreatening(int fromX, int fromY, int toX, int toY, const Board& board) const;
    virtual int getValue() const;
};

#endif //KNIGHT_H
