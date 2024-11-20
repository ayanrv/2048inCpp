#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int GRID_SIZE = 4;

// Function prototypes
void initializeGrid(std::vector<std::vector<int>>& grid);
void displayGrid(const std::vector<std::vector<int>>& grid);
void addRandomTile(std::vector<std::vector<int>>& grid);
bool isGameOver(const std::vector<std::vector<int>>& grid);
bool moveLeft(std::vector<std::vector<int>>& grid, bool& moved);
bool moveRight(std::vector<std::vector<int>>& grid, bool& moved);
bool moveUp(std::vector<std::vector<int>>& grid, bool& moved);
bool moveDown(std::vector<std::vector<int>>& grid, bool& moved);
bool slideAndMerge(std::vector<int>& line, bool& moved);  // Modified to return if any move/merge happened

int main() {
    std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
    char input;

    std::srand(std::time(0));
    initializeGrid(grid);

    while (true) {
        displayGrid(grid);

        if (isGameOver(grid)) {
            std::cout << "Game Over! No more valid moves!" << std::endl;
            break;
        }

        std::cout << "Enter move (W: Up, A: Left, S: Down, D: Right): ";
        std::cin >> input;

        bool validMove = false;
        bool moved = false;

        switch (input) {
        case 'W': case 'w': validMove = moveUp(grid, moved); break;
        case 'A': case 'a': validMove = moveLeft(grid, moved); break;
        case 'S': case 's': validMove = moveDown(grid, moved); break;
        case 'D': case 'd': validMove = moveRight(grid, moved); break;
        default:
            std::cout << "Invalid input. Use W, A, S, D." << std::endl;  // Error message for invalid input
            continue; // Skip the rest of the loop and ask for input again
        }

        // Add a random tile if the grid actually changed (either by slide or merge)
        if (validMove && moved) {
            addRandomTile(grid);
        }
    }

    return 0;
}

// Initialize the grid with two random tiles
void initializeGrid(std::vector<std::vector<int>>& grid) {
    addRandomTile(grid);
    addRandomTile(grid);
}

// Display the grid
void displayGrid(const std::vector<std::vector<int>>& grid) {
    const std::string horizontalBorder = "+----+----+----+----+";

    std::cout << horizontalBorder << std::endl; // Draw top border
    for (const auto& row : grid) {  // Loop through each row of the grid
        for (int cell : row) {   // Loop through each cell in the row
            if (cell == 0) {
                std::cout << "|    "; // Empty cells display as blank
            }
            else {
                std::cout << "| " << cell << " ";
                if (cell < 10) std::cout << " "; // Adjust for single-digit numbers
                else if (cell < 100) std::cout << ""; // Adjust for two-digit numbers
            }
        }
        std::cout << "|" << std::endl; // Close the row
        std::cout << horizontalBorder << std::endl; // Horizontal line between rows
    }
}

// Add a random tile (2 or 4) to an empty cell
void addRandomTile(std::vector<std::vector<int>>& grid) {
    std::vector<std::pair<int, int>> emptyCells;

    // Collect all empty cells
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == 0) { // Check if the cell is empty
                emptyCells.push_back(std::make_pair(i, j)); // Add empty cell to list
            }
        }
    }

    // Add a random tile if there are empty cells
    if (!emptyCells.empty()) { // If there's at least one empty cell
        // Choose a random empty cell
        std::pair<int, int> chosenCell = emptyCells[std::rand() % emptyCells.size()];
        int row = chosenCell.first;
        int col = chosenCell.second;

        // 90% chance for 2, 10% for 4
        grid[row][col] = (std::rand() % 10 < 9) ? 2 : 4;
    }
}

// Check if the game is over
bool isGameOver(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == 0) return false;  // Empty cell found, not over
            if (i < GRID_SIZE - 1 && grid[i][j] == grid[i + 1][j]) return false; // Check down = Vertical mergeable
            if (j < GRID_SIZE - 1 && grid[i][j] == grid[i][j + 1]) return false; // Check right = Horizontal mergeable
        }
    }
    return true; // No moves possible
}

// Helper function to slide and merge a row or column, modified to return if any move/merge happened
bool slideAndMerge(std::vector<int>& line, bool& moved) {
    bool lineChanged = false; // Новый флаг для отслеживания изменений
    int size = line.size();
    // Slide non-zero values to the left
    std::vector<int> newLine(size, 0);
    int index = 0;
    for (int value : line) {
        if (value != 0) {
            newLine[index++] = value;
        }
    }

    if (newLine != line) {  // Проверка: изменился ли массив после сдвига
        lineChanged = true;
    }

    // Merge adjacent tiles
    for (int i = 0; i < size - 1; ++i) {
        if (newLine[i] != 0 && newLine[i] == newLine[i + 1]) {
            newLine[i] *= 2;     // Double the value
            newLine[i + 1] = 0;  // Clear the merged cell
            lineChanged = true; // Маркируем изменение в новый флаг
        }
    }

    // Slide again after merging
    index = 0;
    for (int value : newLine) {
        if (value != 0) {
            line[index++] = value;
        }
    }
    while (index < size) {   // Fill remaining cells with 0
        line[index++] = 0;
    }

    if (lineChanged) {  // Обновление флага движения
        moved = true;
    }

    return lineChanged; // Возвращаем обновление флага движения
}

// Movement functions
bool moveLeft(std::vector<std::vector<int>>& grid, bool& moved) {
    moved = false;
    for (auto& row : grid) {
        bool rowMoved = false;
        slideAndMerge(row, rowMoved);  // Теперь `rowMoved` передается как отдельный флаг
        if (rowMoved) {
            moved = true;  // Обновление флага `moved` при любом изменении строки
        }
    }
    return moved;
}

bool moveRight(std::vector<std::vector<int>>& grid, bool& moved) {
    moved = false;
    for (auto& row : grid) {
        std::reverse(row.begin(), row.end());
        bool rowMoved = false;
        slideAndMerge(row, rowMoved);  // Теперь `rowMoved` передается как отдельный флаг
        if (rowMoved) {
            moved = true;  // Обновление флага `moved` при любом изменении строки
        }
        std::reverse(row.begin(), row.end());
    }
    return moved;
}

bool moveUp(std::vector<std::vector<int>>& grid, bool& moved) {
    moved = false;
    for (int col = 0; col < GRID_SIZE; ++col) {
        std::vector<int> column(GRID_SIZE);
        for (int row = 0; row < GRID_SIZE; ++row) {
            column[row] = grid[row][col];
        }
        bool colMoved = false;
        slideAndMerge(column, colMoved); // Теперь `colMoved` передается как отдельный флаг
        if (colMoved) {
            moved = true; // Обновление флага `moved` при любом изменении строки
        }
        for (int row = 0; row < GRID_SIZE; ++row) {
            grid[row][col] = column[row];
        }
    }
    return moved;
}

bool moveDown(std::vector<std::vector<int>>& grid, bool& moved) {
    moved = false;
    for (int col = 0; col < GRID_SIZE; ++col) {
        std::vector<int> column(GRID_SIZE);
        for (int row = 0; row < GRID_SIZE; ++row) {
            column[row] = grid[GRID_SIZE - 1 - row][col];
        }
        bool colMoved = false;
        slideAndMerge(column, colMoved); // Теперь `colMoved` передается как отдельный флаг
        if (colMoved) {
            moved = true; // Обновление флага `moved` при любом изменении строки
        }
        for (int row = 0; row < GRID_SIZE; ++row) {
            grid[GRID_SIZE - 1 - row][col] = column[row];
        }
    }
    return moved;
}