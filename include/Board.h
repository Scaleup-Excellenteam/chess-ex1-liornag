#pragma once
#include "Piece.h"
#include <memory>
#include <vector>

class Board {
private:
    std::vector<std::vector<std::shared_ptr<Piece>>> board;

public:
    Board(const std::string& layout);
    Piece* getPiece(int x, int y) const;
    void movePiece(int fromX, int fromY, int toX, int toY);
    bool isInCheck(bool isWhite) const;
};
