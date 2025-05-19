//
// Created by liorn on 08/05/2025.
//

#ifndef PAWN_H
#define PAWN_H
#pragma once

#include "Piece.h"

class Move;

class Pawn : public Piece {
private:
    char symbol; // Stores the piece's symbol ('Q' or 'q'), used to identify the player

public:
    Pawn(char symbol);
    char getSymbol() const override;
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override;
    virtual void fillLegalMoves(int fromX, int fromY, std::vector<std::shared_ptr<Move>>& legalMoves, const Board& board) const override;
    virtual bool isThreatening(int fromX, int fromY, int toX, int toY, const Board& board) const;
    virtual int getValue() const;
};

#endif //PAWN_H
