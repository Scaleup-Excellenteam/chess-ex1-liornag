
#ifndef QUEEN_H
#define QUEEN_H

#pragma once
#include "Piece.h"

// The Queen class represents a queen chess piece.
// It inherits from the abstract base class Piece.
class Queen : public Piece {
private:
    char symbol; // Stores the piece's symbol ('Q' or 'q'), used to identify the player

public:
    Queen(char symbol); // Constructor: initializes the queen with its symbol
    char getSymbol() const override;  // Returns the piece's symbol (used to determine type and color)
    bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const override; // Checks whether a move is legal for a queen (combines rook + bishop movement)
};


#endif //QUEEN_H
