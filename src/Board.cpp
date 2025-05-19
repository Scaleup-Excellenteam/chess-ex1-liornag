#include "Board.h"

#include <iostream>


#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"
#include "PriorityQueue.h"
#include "Move.h"
#include "Utils.h"

// Constructor: builds the board from a 64-character layout string
Board::Board(const std::string& layout) {
    // Initialize 8x8 board with null pointers
    board.resize(8, std::vector<std::shared_ptr<Piece>>(8, nullptr));

    // Loop through the layout string and place pieces
    for (int i = 0; i < 64 && i < layout.length(); ++i) {
        char c = layout[i];
        int row = i / 8; // Row index (0–7 from top to bottom)
        int col = i % 8; // Column index (0–7 from left to right)


        // Switch to place correct piece depending on the character
        switch (c) {
            case 'R':board[row][col] = std::make_shared<Rook>('R');
            break;
            case 'r':board[row][col] = std::make_shared<Rook>('r');
            break;
            case 'K':board[row][col] = std::make_shared<King>('K');
            break;
            case 'k':board[row][col] = std::make_shared<King>('k');
            break;
            case 'B': board[row][col] = std::make_shared<Bishop>('B');
            break;
            case 'b': board[row][col] = std::make_shared<Bishop>('b');
            break;
            case 'Q': board[row][col] = std::make_shared<Queen>('Q');
            break;
            case 'q': board[row][col] = std::make_shared<Queen>('q');
            break;
            case 'N': board[row][col] = std::make_shared<Knight>('N');
                break;
            case 'n': board[row][col] = std::make_shared<Knight>('n');
                break;
            case 'P': board[row][col] = std::make_shared<Pawn>('P');
                break;
            case 'p': board[row][col] = std::make_shared<Pawn>('p');
                break;

            default:
                board[row][col] = nullptr; // Empty square or unsupported piece
        }
    }
}

// Returns a pointer to the piece at the given coordinates
Piece* Board::getPiece(int x, int y) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
        return nullptr;  // Out of bounds
    return board[y][x].get();
}

// Moves a piece from (fromX, fromY) to (toX, toY)
void Board::movePiece(int fromX, int fromY, int toX, int toY) {
    board[toY][toX] = board[fromY][fromX];   // Move the piece
    board[fromY][fromX] = nullptr;           // Empty the source square
}

// Checks if the king of the given player is currently in check
bool Board::isInCheck(bool isWhite) const {
    char kingSymbol = isWhite ? 'K' : 'k'; // Use correct symbol for the player's king

    int kingX = -1, kingY = -1;

    // First, locate the king on the board
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* p = getPiece(x, y);
            if (p && p->getSymbol() == kingSymbol) {
                kingX = x;
                kingY = y;
                break;
            }
        }
    }

    if (kingX == -1) return false; /// King not found

    // Now, check if any enemy piece can legally move to the king's position
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* p = getPiece(x, y);
            if (p && !isSameColor(isWhite, p)) { // Opponent's piece
                if (p->isMoveLegal(x, y, kingX, kingY, *this)) {
                    return true; // Enemy piece can attack the king → check
                }
            }
        }
    }

    return false; // No threats found → not in check
}

bool Board::isSameColor(bool isWhite, Piece* p) const {
    if (isupper(p->getSymbol()) && isWhite) {
        return true;
    }
    if (!isupper(p->getSymbol()) && !isWhite) {
        return true;
    }
    return false;
}

std::string Board::getBestMoves(bool isWhite, int movesAmount) const
{
    PriorityQueue<std::shared_ptr<Move>> queue;
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            Piece* p = getPiece(x, y);
            if (p && isSameColor(isWhite, p)) {
                vector<std::shared_ptr<Move>> legalMoves;
                p->fillLegalMoves(x, y, legalMoves, *this);
                fillScores(legalMoves, isWhite);
                for(std::shared_ptr<Move> move : legalMoves)
                {
                    queue.push(move);
                }
            }
        }
    }
    std::string bestMoves;
    int movesNumber = Utils::min(movesAmount, int(queue.size()));
    for (int i = 0; i < movesNumber; i++) {
        if (!queue.isEmpty()) {
            std::shared_ptr<Move> move = queue.poll();
            bestMoves += move->getWalk();
            if (i < movesNumber - 1) {
                bestMoves += ",";
            }
        }
    }
    return bestMoves;
}

bool Board::isInDangerByWeakerPiece(std::shared_ptr<Move> move, bool isWhite) const {
    Piece* piece = getPiece(move->getFromX(), move->getFromY());
    // just in case
    if (piece == nullptr) {
        return false;
    }
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            Piece* p = getPiece(x, y);
            if (p && !isSameColor(isWhite, p) &&
                p->isThreatening(x, x, move->getToX(), move->getToY(), *this) &&
                (p->getValue() < piece->getValue())) {
                return true;
            }
        }
    }
    return false;
}

bool Board::isThreateningOnStrongerPiece(std::shared_ptr<Move> move, bool isWhite) const {
    Piece* piece = getPiece(move->getFromX(), move->getFromY());
    // just in case
    if (piece == nullptr) {
        return false;
    }
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            Piece* p = getPiece(x, y);
            if (p && !isSameColor(isWhite, p) &&
                piece->isThreatening(move->getToX(), move->getToY(), x, y, *this) &&
                (p->getValue() > piece->getValue())) {
                return true;
            }
        }
    }
    return false;
}

bool Board::willEat(std::shared_ptr<Move> move) const {
    Piece* p1 = getPiece(move->getFromX(), move->getFromY());
    Piece* p2 = getPiece(move->getToX(), move->getToY());
    return (p1 != nullptr) && (p2 != nullptr) && (isupper(p1->getSymbol()) != isupper(p2->getSymbol()));
}

void Board::fillScores(std::vector<std::shared_ptr<Move>>& legalMoves, bool isWhite) const {
    for (std::shared_ptr<Move> move : legalMoves)
    {
        move->setScore(10);
        if (isInDangerByWeakerPiece(move, isWhite)) {
            move->increadeScore(-2);
        }
        if (isThreateningOnStrongerPiece(move, isWhite)) {
            move->increadeScore(2);
        }
        if (willEat(move)) {
            move->increadeScore(2);
        }
    }
}
