#include <iostream>
#include "modele.hpp" // Include your original game logic header
#include <curses.h>

// Helper function to print a grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Test the initializeGrid function
void testInitializeGrid() {
    std::cout << "Running testInitializeGrid...\n";
    std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
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

// Test the displayGrid function
void testDisplayGrid() {
    std::cout << "Running testDisplayGrid...\n";
    try {
        std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
        int score = 0;
        displayGrid(grid, score);
        std::cout << "testDisplayGrid passed\n";
    } catch (...) {
        std::cout << "testDisplayGrid failed\n";
    }
}

// Test the addRandomTile function
void testAddRandomTile() {
    std::cout << "Running testAddRandomTile...\n";
    std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
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

void testAddRandomTileEdgeCases() {
    std::cout << "Running testAddRandomTileEdgeCases...\n";
    std::vector<std::vector<int>> grid = {
        {2, 4, 8, 16},
        {32, 64, 128, 256},
        {512, 1024, 2048, 4096},
        {2, 4, 8, 16}
    };

    addRandomTile(grid);

    int nonZeroCount = 0;
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell != 0) nonZeroCount++;
        }
    }

    if (nonZeroCount == 16) {
        std::cout << "testAddRandomTileEdgeCases passed\n";
    } else {
        std::cout << "testAddRandomTileEdgeCases failed\n";
    }
}

// Test the isGameOver function
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

// Test the slideAndMerge function with detailed cases
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

    // Additional test cases
    std::vector<int> noMergeLine = {2, 4, 8, 16};
    moved = false;
    scoreDelta = 0;
    slideAndMerge(noMergeLine, moved, scoreDelta);

    if (noMergeLine == std::vector<int>{2, 4, 8, 16} && !moved && scoreDelta == 0) {
        std::cout << "testSlideAndMerge (no merge) passed\n";
    } else {
        std::cout << "testSlideAndMerge (no merge) failed\n";
    }
}


// Test the moveLeft function
void testMoveLeft() {
    std::cout << "Running testMoveLeft...\n";
    std::vector<std::vector<int>> grid = {
        {2, 2, 0, 0},
        {4, 4, 4, 0},
        {8, 0, 8, 8},
        {16, 0, 0, 16}
    };

    int score = 0;
    bool moved = false;
    moveLeft(grid, moved, score);

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

// Test the moveRight function
void testMoveRight() {
    std::cout << "Running testMoveRight...\n";
    std::vector<std::vector<int>> grid = {
        {0, 0, 2, 2},
        {4, 0, 4, 4},
        {0, 8, 8, 8},
        {0, 16, 0, 16}
    };

    int score = 0;
    bool moved = false;
    moveRight(grid, moved, score);

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



// Test the moveUp function
void testMoveUp() {
    std::cout << "Running testMoveUp...\n";
    std::vector<std::vector<int>> grid = {
        {2, 4, 8, 16},
        {2, 4, 8, 16},
        {0, 0, 8, 16},
        {0, 0, 8, 16}
    };

    std::cout << "Initial Grid:\n";
    printGrid(grid);

    int score = 0;
    bool moved = false;
    moveUp(grid, moved, score);

    std::cout << "Grid After moveUp:\n";
    printGrid(grid);
    std::cout << "Score: " << score << "\n";

    std::vector<std::vector<int>> expected = {
        {4, 8, 16, 32},
        {0, 0, 16, 32},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    if (grid == expected && score == 108) {
        std::cout << "testMoveUp passed\n";
    } else {
        std::cout << "testMoveUp failed\n";
    }
}


// Test the moveDown function
void testMoveDown() {
    std::cout << "Running testMoveDown...\n";
    std::vector<std::vector<int>> grid = {
        {2, 4, 8, 16},
        {2, 4, 8, 16},
        {0, 0, 8, 16},
        {0, 0, 8, 16}
    };

    std::cout << "Initial Grid:\n";
    printGrid(grid);

    int score = 0;
    bool moved = false;
    moveDown(grid, moved, score);

    std::cout << "Grid After moveDown:\n";
    printGrid(grid);
    std::cout << "Score: " << score << "\n";

    std::vector<std::vector<int>> expected = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 16, 32},
        {4, 8, 16, 32}
    };

    if (grid == expected && score == 108) {
        std::cout << "testMoveDown passed\n";
    } else {
        std::cout << "testMoveDown failed\n";
    }
}



// Main function to run all tests
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
     std::cout << "Running additional tests...\n";

    testAddRandomTileEdgeCases();

    std::cout << "Additional tests completed.\n";
    std::cout << "Tests completed.\n";
    return 0;
}
