#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <curses.h> // Include ncurses for screen manipulation
#include <algorithm> // Include algorithm for std::reverse, which is used in movement functions

const int GRID_SIZE = 4; // Define the grid size as a constant

// Function prototypes
void initializeGrid(std::vector<std::vector<int>>& grid);
void displayGrid(const std::vector<std::vector<int>>& grid, int score);
void addRandomTile(std::vector<std::vector<int>>& grid);
bool isGameOver(const std::vector<std::vector<int>>& grid);
bool moveLeft(std::vector<std::vector<int>>& grid, bool& moved, int& score);
bool moveRight(std::vector<std::vector<int>>& grid, bool& moved, int& score);
bool moveUp(std::vector<std::vector<int>>& grid, bool& moved, int& score);
bool moveDown(std::vector<std::vector<int>>& grid, bool& moved, int& score);
bool slideAndMerge(std::vector<int>& line, bool& moved, int& scoreDelta);

int main() {
    std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 0)); // Create a 4x4 grid initialized with zeros
    int score = 0; // Initialize the game score to 0
    char input;    // Variable to store user input

    std::srand(std::time(0)); // Seed the random number generator with the current time for randomness

    // Initialize ncurses
    initscr();          // Start ncurses mode, allowing direct terminal manipulation
    noecho();           // Disable echoing of user input for cleaner display
    cbreak();           // Disable line buffering, making input available immediately
    keypad(stdscr, TRUE); // Enable processing of special keys (like arrows)

    initializeGrid(grid); // Add two random tiles to start the game

    while (true) {
        clear();              // Clear the screen to prepare for a new frame
        displayGrid(grid, score); // Render the grid and current score

        // Check if the game is over
        if (isGameOver(grid)) {
            // If the game is over, display a message and wait for user input to exit
            mvprintw(GRID_SIZE * 2 + 2, 0, "Game Over! No more valid moves!");
            mvprintw(GRID_SIZE * 2 + 3, 0, "Press any key to exit...");
            refresh();        // Update the screen to show the game-over messages
            getch();          // Wait for user input before exiting
            break;            // Exit the main game loop
        }

        // Prompt the user for input
        mvprintw(GRID_SIZE * 2 + 1, 0, "Enter move (W: Up, A: Left, S: Down, D: Right): ");
        refresh();            // Refresh the screen to display the prompt
        input = getch();      // Capture user input using ncurses

        bool validMove = false; // Tracks whether the input corresponds to a valid move
        bool moved = false;    // Tracks whether the grid changed after the move

        // Handle the user's input and perform the corresponding move
        switch (input) {
        case 'W': case 'w': validMove = moveUp(grid, moved, score); break;  // Move tiles up
        case 'A': case 'a': validMove = moveLeft(grid, moved, score); break; // Move tiles left
        case 'S': case 's': validMove = moveDown(grid, moved, score); break; // Move tiles down
        case 'D': case 'd': validMove = moveRight(grid, moved, score); break; // Move tiles right
        default:
            // If input is invalid, display an error message
            mvprintw(GRID_SIZE * 2 + 4, 0, "Invalid input. Use W, A, S, D.");
            refresh();        // Refresh the screen to show the error message
            continue;         // Skip further processing and ask for input again
        }

        // If the move was valid and the grid changed, add a new random tile
        if (validMove && moved) {
            addRandomTile(grid);
        }
    }

    endwin(); // End ncurses mode and restore the terminal to its original settings
    return 0;
}

// Add two random tiles to the grid to start the game
void initializeGrid(std::vector<std::vector<int>>& grid) {
    addRandomTile(grid);
    addRandomTile(grid);
}

void displayGrid(const std::vector<std::vector<int>>& grid, int score) {
    const std::string horizontalBorder = "+----+----+----+----+"; // Define the horizontal border for the grid

    // Clear the screen
    clear();

    // Draw the grid
    for (int i = 0; i < GRID_SIZE; ++i) {
        mvprintw(i * 2, 0, horizontalBorder.c_str()); // Print the horizontal border for each row
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == 0) {
                mvprintw(i * 2 + 1, j * 5, "|    "); // Empty cell
            } else {
                mvprintw(i * 2 + 1, j * 5, "|%4d", grid[i][j]); // Right-aligned numbers
            }
        }
        mvprintw(i * 2 + 1, GRID_SIZE * 5, "|"); // Close the row with a vertical bar
    }
    mvprintw(GRID_SIZE * 2, 0, horizontalBorder.c_str()); // Print the bottom border of the grid

    // Add extra space to separate the score from the grid
    mvprintw(GRID_SIZE * 2 + 1, 0, ""); // Ensure no overlapping happens here

    // Display the score directly below the grid
    mvprintw(GRID_SIZE * 2 + 2, 0, "Score: %d", score); // Adjusted position for the score count

    // Refresh the screen to apply the changes
    refresh();
}



// Add a random tile (2 or 4) to an empty cell in the grid
void addRandomTile(std::vector<std::vector<int>>& grid) {
    std::vector<std::pair<int, int>> emptyCells;

    // Find all empty cells in the grid
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == 0) {
                emptyCells.emplace_back(i, j);
            }
        }
    }

    // If no empty cells are left, return
    if (emptyCells.empty()) {
        return;
    }

    // Select a random empty cell and place a 2 or 4
    int randomIndex = std::rand() % emptyCells.size();
    int value = (std::rand() % 10 < 9) ? 2 : 4; // 90% chance for a 2, 10% for a 4
    grid[emptyCells[randomIndex].first][emptyCells[randomIndex].second] = value;
}
// Other functions (isGameOver, slideAndMerge, movement functions) remain unchanged

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