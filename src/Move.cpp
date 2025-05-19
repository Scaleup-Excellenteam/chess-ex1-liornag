#include "Move.h"

Move::Move(int fromX, int fromY, int toX, int toY, int score) : fromX(fromX), fromY(fromY), toX(toX), toY(toY),
                                                                score(score) {
}

int Move::getFromX() const {
    return fromX;
}

int Move::getFromY() const {
    return fromY;
}

int Move::getToX() const {
    return toX;
}

int Move::getToY() const {
    return toY;
}

int Move::getScore() const {
    return score;
}

void Move::setScore(int score) {
    score = score;
}

const string Move::getWalk() const {
    // Generates the walk
    string walk;
    walk = static_cast<char>('a' + fromY);
    walk += static_cast<char>('1' + fromX);
    walk += static_cast<char>('a' + toY);
    walk += static_cast<char>('1' + toX);
    return walk;
}

int Move::operator-(const Move &other) const {
    return score - other.score;
}

int operator-(const std::shared_ptr<Move>& me, const std::shared_ptr<Move>& other) {
    return *me - *other;
}

void Move::increadeScore(int delta) {
    score += delta;
}
