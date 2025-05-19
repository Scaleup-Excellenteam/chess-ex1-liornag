#pragma once

#include <string>
#include <memory>

using namespace std;

// This class will help us with the information about each move
class Move {
private:
    int fromX;
    int fromY;
    int toX;
    int toY;
    int score;

public:
    // Constructor
    Move(int fromX, int fromY, int toX, int toY, int score = 0);

    // Simple getters
    int getFromX() const;

    int getFromY() const;

    int getToX() const;

    int getToY() const;

    int getScore() const;

    void setScore(int score);

    void increadeScore(int delta);

    const string getWalk() const;

    // To use with my PriorityQueue
    int operator-(const Move &other) const;
};

// To use with my PriorityQueue
int operator-(const std::shared_ptr<Move>& me, const std::shared_ptr<Move>& other);
