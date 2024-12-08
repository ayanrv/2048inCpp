#include "ai.hpp"
#include "modele.hpp"  // Include game logic functions
#include <vector>
#include <string>
#include <climits>

/////////////////////////////////////////////////////////////////////////////////
// Function: evaluateGrid
// Description: Evaluates the current game grid using a weighted heuristic that 
//              considers score, empty tiles, monotonicity, and merge potential.
// Parameters:
//   - grid: The current state of the game grid as a 2D vector of integers.
// Returns: An integer representing the evaluation score of the grid.
/////////////////////////////////////////////////////////////////////////////////
int evaluateGrid(const std::vector<std::vector<int>>& grid) {
    int emptyTiles = 0;      // Count of empty tiles in the grid
    int score = 0;           // Total sum of all tile values (game score)
    int monotonicity = 0;    // Tracks the smoothness/order of tiles
    int mergePotential = 0;  // Tracks mergeable tile pairs

    // Traverse the entire grid to calculate evaluation components
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == 0) emptyTiles++;  // Count empty tiles
            score += grid[i][j];               // Add tile value to total score
        }
    }

    // Calculate monotonicity for both rows and columns
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size() - 1; ++j) {
            // Row-wise monotonicity check (left to right)
            if (grid[i][j] >= grid[i][j + 1]) monotonicity++;
            
            // Column-wise monotonicity check (top to bottom)
            if (grid[j][i] >= grid[j + 1][i]) monotonicity++;
        }
    }

    // Count adjacent merge potential for rows and columns
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size() - 1; ++j) {
            // Check horizontal merges (left to right)
            if (grid[i][j] == grid[i][j + 1]) mergePotential++;
            
            // Check vertical merges (top to bottom)
            if (grid[j][i] == grid[j + 1][i]) mergePotential++;
        }
    }

    // Return the weighted evaluation score
    // Weights:
    // - Empty tiles (200): Keeps more available moves
    // - Monotonicity (50): Keeps tiles ordered
    // - Merge Potential (100): Encourages merges
    return score + emptyTiles * 200 + monotonicity * 50 + mergePotential * 100;
}

/////////////////////////////////////////////////////////////////////////////////
// Function: getBestMove
// Description: Determines the best move using a three-step lookahead by 
//              evaluating all possible moves and selecting the most optimal path.
// Parameters:
//   - grid: The current game grid as a 2D vector of integers.
//   - currentScore: The current game score.
// Returns: A string representing the best move ("Up", "Down", "Left", "Right").
/////////////////////////////////////////////////////////////////////////////////
std::string getBestMove(const std::vector<std::vector<int>>& grid, int currentScore) {
    int maxEvaluation = INT_MIN;  // Store the best evaluation score found
    std::string bestMove = "None";  // Track the best move based on evaluation

    // Temporary grids for simulating moves at different depths
    std::vector<std::vector<int>> tempGrid, futureGrid, thirdGrid;
    int score, futureScore, thirdScore;  // Track scores after simulated moves
    bool moved, futureMoved, thirdMoved;  // Track whether a move was successful

    // First-level move evaluation
    for (int move = 0; move < 4; ++move) {
        tempGrid = grid;  // Reset the grid to the original state
        score = currentScore;
        moved = false;

        // Simulate the first move
        switch (move) {
            case 0: moveUp(tempGrid, moved, score); break;      // Simulate Up
            case 1: moveDown(tempGrid, moved, score); break;    // Simulate Down
            case 2: moveLeft(tempGrid, moved, score); break;    // Simulate Left
            case 3: moveRight(tempGrid, moved, score); break;   // Simulate Right
        }

        if (!moved) continue;  // Skip move if no tiles were moved

        // Second-level move evaluation
        for (int nextMove = 0; nextMove < 4; ++nextMove) {
            futureGrid = tempGrid;  // Reset grid after first move
            futureScore = score;    // Reset score after first move
            futureMoved = false;

            // Simulate the second move
            switch (nextMove) {
                case 0: moveUp(futureGrid, futureMoved, futureScore); break;   // Simulate Up
                case 1: moveDown(futureGrid, futureMoved, futureScore); break; // Simulate Down
                case 2: moveLeft(futureGrid, futureMoved, futureScore); break; // Simulate Left
                case 3: moveRight(futureGrid, futureMoved, futureScore); break;// Simulate Right
            }

            if (!futureMoved) continue;  // Skip if no tiles moved in second move

            // Third-level move evaluation
            for (int lastMove = 0; lastMove < 4; ++lastMove) {
                thirdGrid = futureGrid;  // Reset grid after second move
                thirdScore = futureScore;  // Reset score after second move
                thirdMoved = false;

                // Simulate the third move
                switch (lastMove) {
                    case 0: moveUp(thirdGrid, thirdMoved, thirdScore); break;   // Simulate Up
                    case 1: moveDown(thirdGrid, thirdMoved, thirdScore); break; // Simulate Down
                    case 2: moveLeft(thirdGrid, thirdMoved, thirdScore); break; // Simulate Left
                    case 3: moveRight(thirdGrid, thirdMoved, thirdScore); break;// Simulate Right
                }

                if (!thirdMoved) continue;  // Skip if no tiles moved in third move

                // Evaluate the grid after three moves
                int evaluation = evaluateGrid(thirdGrid);

                // Update the best move if this path is better
                if (evaluation > maxEvaluation) {
                    maxEvaluation = evaluation;
                    switch (move) {
                        case 0: bestMove = "Up"; break;
                        case 1: bestMove = "Down"; break;
                        case 2: bestMove = "Left"; break;
                        case 3: bestMove = "Right"; break;
                    }
                }
            }
        }
    }

    // Return the best evaluated move
    return bestMove;
}
