#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

const int GRID_SIZE = 4;

// Function prototypes
void initializeGrid(int grid[GRID_SIZE][GRID_SIZE]);
void displayGrid(int grid[GRID_SIZE][GRID_SIZE]);
void addRandomTile(int grid[GRID_SIZE][GRID_SIZE]);
bool isGameOver(int grid[GRID_SIZE][GRID_SIZE]);

int main() {
    int grid[GRID_SIZE][GRID_SIZE] = {0}; // 4x4 grid initialized to 0
    char input;

    std::srand(std::time(0)); // Seed random number generator
    initializeGrid(grid);

    while (true) {
        displayGrid(grid);

        if (isGameOver(grid)) {
            std::cout << "Game Over! No more valid moves!" << std::endl;
            break;
        }

        std::cout << "Enter move (W: Up, A: Left, S: Down, D: Right): ";
        std::cin >> input;

        // TODO: Handle moves based on input
        // Implement functions to handle moves: moveUp(), moveLeft(), moveDown(), moveRight()

        // Add a new random tile after a valid move
        addRandomTile(grid);
    }

    return 0;
}

// Initialize the grid with two random tiles
void initializeGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    addRandomTile(grid);
    addRandomTile(grid);
}

// Display the grid neatly
void displayGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    std::cout << "+---------------------+" << std::endl;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            std::cout << "| " << std::setw(4);
            if (grid[i][j] != 0)
                std::cout << grid[i][j];
            else
                std::cout << " ";
        }
        std::cout << " |" << std::endl;
        std::cout << "+---------------------+" << std::endl;
    }
}

// Add a random tile (2 or 4) to an empty position
void addRandomTile(int grid[GRID_SIZE][GRID_SIZE]) {
    int emptyCells[GRID_SIZE * GRID_SIZE][2];
    int emptyCount = 0;

    // Find all empty cells
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == 0) {
                emptyCells[emptyCount][0] = i;
                emptyCells[emptyCount][1] = j;
                ++emptyCount;
            }
        }
    }

    if (emptyCount > 0) {
        // Pick a random empty cell
        int randomIndex = std::rand() % emptyCount;
        int row = emptyCells[randomIndex][0];
        int col = emptyCells[randomIndex][1];

        // Place a 2 (90%) or 4 (10%) in the chosen cell
        grid[row][col] = (std::rand() % 10 == 0) ? 4 : 2;
    }
}

// Check if the game is over (no valid moves)
bool isGameOver(int grid[GRID_SIZE][GRID_SIZE]) {
    // Check for empty cells
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == 0)
                return false;
        }
    }

    // Check for adjacent tiles with the same value
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE - 1; ++j) {
            if (grid[i][j] == grid[i][j + 1] || grid[j][i] == grid[j + 1][i])
                return false;
        }
    }

    return true; // No empty cells or valid merges left
}
