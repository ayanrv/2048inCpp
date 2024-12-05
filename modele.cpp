#include "modele.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <curses.h>
#include <iostream>
#include <vector>

// Initialize ncurses color pairs for tiles and borders
void initializeColors() {
    start_color(); // Enable color functionality in ncurses
    use_default_colors(); // Use default terminal colors as base

    // Array of background colors for tiles
    int tileColors[] = {COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_CYAN,
                        COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE};

    // Create color pairs for tiles (white text, colorful background)
    for (int i = 0; i < 7; ++i) {
        init_pair(i + 1, COLOR_WHITE, tileColors[i]); // Tile colors
    }

    // Create color pairs for borders (cycle through bright colors)
    init_pair(8, COLOR_YELLOW, -1);    // Horizontal border
    init_pair(9, COLOR_YELLOW, -1); // Vertical border
}

// Map a tile value (e.g., 2, 4, 8, ...) to a color pair index
int getColorPairIndex(int value) {
    if (value == 0) return -1; // Return -1 for no color (empty tiles)
    int colorCount = 7; // Total number of defined colors
    int index = 0; // Start with the first color pair

    // Determine the index based on the power of 2
    while (value > 1) {
        value /= 2;
        ++index;
    }

    return (index - 1) % colorCount + 1; // Cycle through the colors dynamically
}

// Initialize the grid with two random tiles
void initializeGrid(std::vector<std::vector<int>>& grid) {
    addRandomTile(grid); // Add the first random tile
    addRandomTile(grid); // Add the second random tile
}

// Display the game grid with tiles and score
void displayGrid(const std::vector<std::vector<int>>& grid, int score) {
    const char* horizontalBorder = "+-----+-----+-----+-----+"; // Horizontal border format

    clear();
    for (int i = 0; i < grid.size(); ++i) {
        // Print horizontal border with a specific color
        attron(COLOR_PAIR(8));
        mvprintw(i * 2, 0, "%s", horizontalBorder);
        attroff(COLOR_PAIR(8));

        for (int j = 0; j < grid[i].size(); ++j) {
            // Print vertical borders with a specific color
            attron(COLOR_PAIR(9));
            mvprintw(i * 2 + 1, j * 6, "|");
            attroff(COLOR_PAIR(9));

            int value = grid[i][j];
            int colorPair = getColorPairIndex(value);

            // Print the tile value or leave empty space
            if (value == 0) {
                mvprintw(i * 2 + 1, j * 6 + 1, "     "); // Empty cell
            } else {
                attron(COLOR_PAIR(colorPair));
                mvprintw(i * 2 + 1, j * 6 + 1, " %4d", value); // Tile value
                attroff(COLOR_PAIR(colorPair));
            }
        }

        // Close the row with the final vertical border
        attron(COLOR_PAIR(9));
        mvprintw(i * 2 + 1, grid[0].size() * 6, "|");
        attroff(COLOR_PAIR(9));
    }

    // Print the final horizontal border
    attron(COLOR_PAIR(8));
    mvprintw(grid.size() * 2, 0, "%s", horizontalBorder);
    attroff(COLOR_PAIR(8));

    // Display the score below the grid
    mvprintw(grid.size() * 2 + 3, 0, "Score: %d", score);
    refresh(); // Refresh the screen to show changes
}

// Add a random tile (2 or 4) to an empty cell
void addRandomTile(std::vector<std::vector<int>>& grid) {
    std::vector<std::pair<int, int>> emptyCells; // List of empty cells

    // Find all empty cells in the grid
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == 0) {
                emptyCells.emplace_back(i, j); // Add empty cell to the list
            }
        }
    }

    // If no empty cells are available, do nothing
    if (emptyCells.empty()) return;

    // Select a random empty cell and place a 2 or 4
    int randomIndex = std::rand() % emptyCells.size(); //std::rand() generates a random integer and % emptyCells.size() ensures the index is within the valid range of emptyCells. 
    int value = (std::rand() % 10 < 9) ? 2 : 4; // 90% chance for 2, 10% for 4
    grid[emptyCells[randomIndex].first][emptyCells[randomIndex].second] = value; //Accesses the grid cell at the row emptyCells[randomIndex].first and column emptyCells[randomIndex].second. Assigns the value (2 or 4) to that cell.
}

// Check if the game is over
bool isGameOver(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < GRID_SIZE; ++i) { // Loop through rows
        for (int j = 0; j < GRID_SIZE; ++j) { // Loop through columns
            if (grid[i][j] == 0) return false; // Empty cell found, not over
            if (i < GRID_SIZE - 1 && grid[i][j] == grid[i + 1][j]) return false; // Vertical merge possible
            if (j < GRID_SIZE - 1 && grid[i][j] == grid[i][j + 1]) return false; // Horizontal merge possible
        }
    }
    return true; // No moves possible
}

// Helper function to slide and merge a row or column, modified to return if any move/merge happened
bool slideAndMerge(std::vector<int>& line, bool& moved, int& scoreDelta) {
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
            scoreDelta += newLine[i]; //Update score for the merged value
            newLine[i + 1] = 0;  // Clear the merged cell
            lineChanged = true; // Маркируем изменение в новый флаг
            i++; // Skip the next tile to avoid double merge
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

     // Check if the line has changed
    if (line != newLine) {
        moved = true;
    }


    return lineChanged; // Возвращаем обновление флага движения
}

// Movement functions
bool moveLeft(std::vector<std::vector<int>>& grid, bool& moved, int& score) {
    moved = false;
    int scoreDelta = 0;
    for (auto& row : grid) {
        bool rowMoved = false;
        slideAndMerge(row, rowMoved, scoreDelta);  // Теперь `rowMoved` передается как отдельный флаг
        if (rowMoved) {
            moved = true;  // Обновление флага `moved` при любом изменении строки
        }
    }
    score += scoreDelta; // Update the score after merging
    return moved;
}

bool moveRight(std::vector<std::vector<int>>& grid, bool& moved, int& score) {
    moved = false;
    int scoreDelta = 0;
    for (auto& row : grid) {
        std::reverse(row.begin(), row.end());
        bool rowMoved = false;
        slideAndMerge(row, rowMoved, scoreDelta);  // Теперь `rowMoved` передается как отдельный флаг
        if (rowMoved) {
            moved = true;  // Обновление флага `moved` при любом изменении строки
        }
        std::reverse(row.begin(), row.end());
    }
    score += scoreDelta;
    return moved;
}

bool moveUp(std::vector<std::vector<int>>& grid, bool& moved, int& score) {
    moved = false;
    int scoreDelta = 0;
    for (int col = 0; col < GRID_SIZE; ++col) {
        std::vector<int> column(GRID_SIZE);
        for (int row = 0; row < GRID_SIZE; ++row) {
            column[row] = grid[row][col];
        }
        bool colMoved = false;
        slideAndMerge(column, colMoved, scoreDelta); // Теперь `colMoved` передается как отдельный флаг
        if (colMoved) {
            moved = true; // Обновление флага `moved` при любом изменении строки
        }
        for (int row = 0; row < GRID_SIZE; ++row) {
            grid[row][col] = column[row];
        }
    }
    score += scoreDelta; // Update the score after merging
    return moved;
}

bool moveDown(std::vector<std::vector<int>>& grid, bool& moved, int& score) {
    moved = false;
    int scoreDelta = 0;
    for (int col = 0; col < GRID_SIZE; ++col) {
        std::vector<int> column(GRID_SIZE);
        for (int row = 0; row < GRID_SIZE; ++row) {
            column[row] = grid[GRID_SIZE - 1 - row][col];
        }
        bool colMoved = false;
        slideAndMerge(column, colMoved, scoreDelta); // Теперь `colMoved` передается как отдельный флаг
        if (colMoved) {
            moved = true; // Обновление флага `moved` при любом изменении строки
        }
        for (int row = 0; row < GRID_SIZE; ++row) {
            grid[GRID_SIZE - 1 - row][col] = column[row];
        }
    }
    score += scoreDelta; // Update the score after merging
    return moved;
}