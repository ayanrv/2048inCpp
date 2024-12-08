#ifndef AI_HPP
#define AI_HPP

#include <vector>
#include <string>

// Function to get the best move based on the current grid and score
std::string getBestMove(const std::vector<std::vector<int>>& grid, int currentScore);

int evaluateGrid(const std::vector<std::vector<int>>& grid);

#endif // AI_HPP
