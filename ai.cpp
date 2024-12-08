#include "ai.hpp"
#include "modele.hpp" // Include for move functions
#include <vector>
#include <string>

std::string getBestMove(const std::vector<std::vector<int>>& grid, int currentScore) {
    int maxScore = currentScore;
    std::string bestMove = "None"; // Default to no move
    bool moved;
    int score;

    // Simulate Move Up
    std::vector<std::vector<int>> tempGrid = grid;
    score = currentScore;
    moved = false;
    moveUp(tempGrid, moved, score);
    if (moved && score > maxScore) {
        maxScore = score;
        bestMove = "Up";
    }

    // Simulate Move Down
    tempGrid = grid;
    score = currentScore;
    moved = false;
    moveDown(tempGrid, moved, score);
    if (moved && score > maxScore) {
        maxScore = score;
        bestMove = "Down";
    }

    // Simulate Move Left
    tempGrid = grid;
    score = currentScore;
    moved = false;
    moveLeft(tempGrid, moved, score);
    if (moved && score > maxScore) {
        maxScore = score;
        bestMove = "Left";
    }

    // Simulate Move Right
    tempGrid = grid;
    score = currentScore;
    moved = false;
    moveRight(tempGrid, moved, score);
    if (moved && score > maxScore) {
        maxScore = score;
        bestMove = "Right";
    }

    return bestMove;
}
