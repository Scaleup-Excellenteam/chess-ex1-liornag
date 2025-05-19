
#ifndef BISHOP_H
#define BISHOP_H

#pragma once
#include "Piece.h"

// The Bishop class represents a bishop chess piece.
// It inherits from the base Piece class and implements its movement logic.
class Bishop : public Piece {
private:
    char symbol; // Stores the piece's symbol ('B' for white, 'b' for black)

public:
    // Constructor: initializes the bishop with its symbol
    Bishop(char symbol);
    // Returns the piece's symbol (used to determine type and color)
    char getSymbol() const override;
    // Checks whether a move is legal for a bishop (diagonal movement only)
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override;
    virtual void fillLegalMoves(int fromX, int fromY, std::vector<std::shared_ptr<Move>>& legalMoves, const Board& board) const override;
    virtual bool isThreatening(int fromX, int fromY, int toX, int toY, const Board& board) const;
    virtual int getValue() const;
};

#endif //BISHOP_H