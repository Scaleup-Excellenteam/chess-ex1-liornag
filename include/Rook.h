
#ifndef ROOK_H
#define ROOK_H

#pragma once
#include "Piece.h"

// The Rook class represents a rook chess piece.
// It inherits from the abstract base class Piece.
class Rook : public Piece {
private:
    char symbol;  // Stores the piece symbol ('R' for white, 'r' for black)


public:
    Rook(char symbol);  // Constructor: initializes the rook with its symbol
    char getSymbol() const override;  // Returns the symbol of the piece ('R' or 'r')
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override;  // Checks whether the rook's move is legal (horizontal or vertical only)
    virtual void fillLegalMoves(int fromX, int fromY, std::vector<std::shared_ptr<Move>>& legalMoves, const Board& board) const override;
    virtual bool isThreatening(int fromX, int fromY, int toX, int toY, const Board& board) const;
    virtual int getValue() const;
};

#endif //ROOK_H