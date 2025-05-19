#pragma once

#include <vector>
#include <memory>

class Board; // Forward declaration – avoids circular dependency with Board class
class Move;

// Abstract base class for all chess pieces
class Piece {
public:
    // Pure virtual function to check if a move is legal for this piece type
    // Must be implemented by derived classes (e.g. Rook, Bishop, King, etc.)
    virtual bool isMoveLegal(int fromX, int fromY, int toX, int toY, const Board& board) const = 0;
    // Pure virtual function to return the symbol of the piece ('R', 'Q', 'k', etc.)
    virtual char getSymbol() const = 0;
    // Virtual destructor – ensures correct cleanup of derived classes
    virtual ~Piece() = default;
    virtual void fillLegalMoves(int fromX, int fromY, std::vector<std::shared_ptr<Move>>& legalMoves, const Board& board) const = 0;
    virtual bool isThreatening(int fromX, int fromY, int toX, int toY, const Board& board) const = 0;
    virtual int getValue() const = 0;
};