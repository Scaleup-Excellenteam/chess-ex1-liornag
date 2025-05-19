//
// Created by liorn on 09/04/2025.
//

#ifndef KING_H
#define KING_H
#pragma once
#include "Piece.h"

// The King class represents a king chess piece.
// It inherits from the abstract base class Piece.
class King : public Piece {
private:
    char symbol; // Stores the piece symbol ('K' or 'k') to indicate color

public:
    King(char symbol); // Constructor: initializes the king with its symbol
    char getSymbol() const override;// Returns the symbol of the piece (used to check piece type and player color)
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override; // Checks whether the king's move is legal (1 square in any direction)
    virtual void fillLegalMoves(int fromX, int fromY, std::vector<std::shared_ptr<Move>>& legalMoves, const Board& board) const override;
    virtual bool isThreatening(int fromX, int fromY, int toX, int toY, const Board& board) const;
    virtual int getValue() const;
};

#endif //KING_H