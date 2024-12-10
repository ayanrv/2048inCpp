#include <iostream>
#include <vector>
#include "modele.hpp" // Include your original game logic header
#include "menu.hpp"   // For saveBestScore/loadBestScore

// Function to display a grid.
// Parameter: 
// "grid": a two-dimensional matrix containing the grid values.
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Checks that the `initializeGrid` function correctly initializes the grid with 2 non-zero tiles.
// Success criterion: The grid contains exactly 2 non-zero cells after initialization.
void testInitializeGrid() {
    std::cout << "Running testInitializeGrid...\n";
    std::vector<std::vector<int>> grid(4, std::vector<int>(4, 0)); 
    initializeGrid(grid);

    int nonZeroCount = 0;
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell != 0) nonZeroCount++;
        }
    }

    if (nonZeroCount == 2) {
        std::cout << "testInitializeGrid passed\n";
    } else {
        std::cout << "testInitializeGrid failed\n";
    }
}

// Tests the `displayGrid` function for correctly displaying the grid and the score.
// Success criterion: No errors during execution.
void testDisplayGrid() {
    std::cout << "Running testDisplayGrid...\n";
    try {
        std::vector<std::vector<int>> grid(4, std::vector<int>(4, 0));
        int score = 0;
        int bestScore = 1000; // Just for display
        displayGrid(grid, score, bestScore);
        std::cout << "testDisplayGrid passed\n";
    } catch (...) {
        std::cout << "testDisplayGrid failed\n";
    }
}

// Tests adding a random tile to an empty grid.
// Success criterion: The grid contains exactly one non-zero cell after the addition.
void testAddRandomTile() {
    std::cout << "Running testAddRandomTile...\n";
    std::vector<std::vector<int>> grid(4, std::vector<int>(4, 0));
    addRandomTile(grid);

    int nonZeroCount = 0;
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell != 0) nonZeroCount++;
        }
    }

    if (nonZeroCount == 1) {
        std::cout << "testAddRandomTile passed\n";
    } else {
        std::cout << "testAddRandomTile failed\n";
    }
}

// Tests whether the `isGameOver` function correctly detects the end of the game.
// Success cases: 
// - Returns `true` if no combination or move is possible.
// - Returns `false` if a move or combination is still possible.
void testIsGameOver() {
    std::cout << "Running testIsGameOver...\n";
    std::vector<std::vector<int>> grid = {
        {2, 4, 8, 16},
        {32, 64, 128, 256},
        {512, 1024, 2048, 4096},
        {2, 4, 8, 16}
    };

    if (isGameOver(grid)) {
        std::cout << "testIsGameOver (over state) passed\n";
    } else {
        std::cout << "testIsGameOver (over state) failed\n";
    }

    grid[3][3] = 8; // Make a valid move possible
    if (!isGameOver(grid)) {
        std::cout << "testIsGameOver (not over state) passed\n";
    } else {
        std::cout << "testIsGameOver (not over state) failed\n";
    }
}

// Tests sliding and merging a row in the grid.
// Success case: 
// - Tiles merge correctly, and scores are updated.
void testSlideAndMerge() {
    std::cout << "Running testSlideAndMerge...\n";

    std::vector<int> line = {2, 2, 4, 4};
    bool moved = false;
    int scoreDelta = 0;
    slideAndMerge(line, moved, scoreDelta);

    if (line == std::vector<int>{4, 8, 0, 0} && scoreDelta == 12) {
        std::cout << "testSlideAndMerge passed\n";
    } else {
        std::cout << "testSlideAndMerge failed\n";
    }
}

// Tests moving and merging tiles during a leftward move.
// Success criterion: The final grid matches the expected state, and the score is correct.
void testMoveLeft() {
    std::cout << "Running testMoveLeft...\n";
    std::vector<std::vector<int>> grid = {
        {2, 2, 0, 0},
        {4, 4, 4, 0},
        {8, 0, 8, 8},
        {16, 0, 0, 16}
    };

    std::cout << "Initial Grid:\n";
    printGrid(grid);

    int score = 0;
    bool moved = false;
    moveLeft(grid, moved, score);

    std::cout << "Grid After moveLeft:\n";
    printGrid(grid);

    std::vector<std::vector<int>> expected = {
        {4, 0, 0, 0},
        {8, 4, 0, 0},
        {16, 8, 0, 0},
        {32, 0, 0, 0}
    };

    if (grid == expected && score == 60) {
        std::cout << "testMoveLeft passed\n";
    } else {
        std::cout << "testMoveLeft failed\n";
    }
}

// Tests moving and merging tiles during a rightward move.
void testMoveRight() {
    std::cout << "Running testMoveRight...\n";
    std::vector<std::vector<int>> grid = {
        {0, 0, 2, 2},
        {4, 0, 4, 4},
        {0, 8, 8, 8},
        {0, 16, 0, 16}
    };

    std::cout << "Initial Grid:\n";
    printGrid(grid);

    int score = 0;
    bool moved = false;
    moveRight(grid, moved, score);

    std::cout << "Grid After moveRight:\n";
    printGrid(grid);

    std::vector<std::vector<int>> expected = {
        {0, 0, 0, 4},
        {0, 0, 4, 8},
        {0, 0, 8, 16},
        {0, 0, 0, 32}
    };

    if (grid == expected && score == 60) {
        std::cout << "testMoveRight passed\n";
    } else {
        std::cout << "testMoveRight failed\n";
    }
}

// Tests tile movement and merging when moving up.
void testMoveUp() {
    std::cout << "Running testMoveUp...\n";
    std::vector<std::vector<int>> grid = {
        {2, 0, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    std::cout << "Initial Grid:\n";
    printGrid(grid);

    int score = 0;
    bool moved = false;
    moveUp(grid, moved, score);

    std::cout << "Grid After moveUp:\n";
    printGrid(grid);

    std::vector<std::vector<int>> expected = {
        {4, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    if (grid == expected && score == 4) {
        std::cout << "testMoveUp passed\n";
    } else {
        std::cout << "testMoveUp failed\n";
    }
}

// Tests tile movement and merging when moving down.
void testMoveDown() {
    std::cout << "Running testMoveDown...\n";
    std::vector<std::vector<int>> grid = {
        {2, 0, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    std::cout << "Initial Grid:\n";
    printGrid(grid);

    int score = 0;
    bool moved = false;
    moveDown(grid, moved, score);

    std::cout << "Grid After moveDown:\n";
    printGrid(grid);

    std::vector<std::vector<int>> expected = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {4, 0, 0, 0}
    };

    if (grid == expected && score == 4) {
        std::cout << "testMoveDown passed\n";
    } else {
        std::cout << "testMoveDown failed\n";
    }
}


// Main function to run all tests.
int main() {
    std::cout << "Running tests...\n";
    testInitializeGrid();
    testDisplayGrid();
    testAddRandomTile();
    testIsGameOver();
    testSlideAndMerge();
    testMoveLeft();
    testMoveRight();
    testMoveUp();
    testMoveDown();
    std::cout << "All tests completed.\n";
    return 0;
}
