#pragma once
#include "Piece.h"
#include <memory>
#include <vector>

// The Board class represents the 8x8 chessboard and manages piece placement and movement.
class Board {
private:
    // 8x8 grid of shared pointers to Piece objects (nullptr if square is empty)
    std::vector<std::vector<std::shared_ptr<Piece>>> board;

public:
    Board(const std::string& layout); // Constructor: builds the board based on a 64-character layout string
    Piece* getPiece(int x, int y) const; // Returns a raw pointer to the piece at (x, y), or nullptr if empty
    void movePiece(int fromX, int fromY, int toX, int toY); // Moves a piece from (fromX, fromY) to (toX, toY)
    bool isInCheck(bool isWhite) const; // Checks whether the given player (white = true, black = false) is currently in check
};
