#include "modele.hpp"
#include "menu.hpp"  // Include the menu header
#include "ai.hpp"
#include <chrono>    // For timed mode support
#include <curses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

// Main function to run the game
int main() {
    int gridSize = 4;     // Default grid size
    int score = 0; // Initialize the game score
    int bestScore = loadBestScore(); // Load the best score from the file
    int input; // Use int instead of char for user input
    bool undoAvailable = false; // Track if undo is available
    int prevScore = 0;      // Store the previous score
    std::string currentHint = "";

    // Before initializing the grid
    bool timedMode = false;
    int timeLimit = 120;  // Default time limit for timed mode

     // Call the menu to set gridSize, timedMode, and timeLimit
    showMenu(timedMode, timeLimit, gridSize);

    // Initialize the grid dynamically based on gridSize
    std::vector<std::vector<int>> grid(gridSize, std::vector<int>(gridSize, 0)); // Current grid
    std::vector<std::vector<int>> prevGrid(gridSize, std::vector<int>(gridSize, 0)); // Previous grid

    std::srand(std::time(0)); // Seed random number generator for random tile placement
    
    // Initialize ncurses screen
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); // Enable arrow key input

    initializeColors(); // Initialize color pairs for the game
    initializeGrid(grid); // Add two random tiles to start the game

    auto startTime = std::chrono::steady_clock::now();

    // Main game loop
    while (true) {
        clear(); // Clear the screen to prepare for drawing the grid
        displayGrid(grid, score, bestScore); // Display the grid, score, and best score

        // Check timer only if timed mode is enabled
        if (timedMode) {
            auto now = std::chrono::steady_clock::now();
            int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

             mvprintw(gridSize * 2 + 6, 0, "Time left: %d seconds", timeLimit - elapsed);

            if (elapsed >= timeLimit) {
                mvprintw(gridSize * 2 + 6, 0, "Time's up! Game over.");
                refresh();
                getch();
                break;
            }
        }

        // Check if the game is over
        if (isGameOver(grid)) {
            mvprintw(gridSize * 2 + 5, 0, "Game Over! No more valid moves!"); // Game over message
            mvprintw(gridSize * 2 + 6, 0, "Press any key to exit...");
            refresh(); // Refresh the screen to show game-over messages
            getch(); // Wait for user input to acknowledge the game over
            break; // Exit the main game loop
        }

        // Show hint if available
        if (!currentHint.empty()) {
            mvprintw(gridSize * 2 + 9, 0, "Hint: %s", currentHint.c_str());
        }

        // Show instructions for player input
        mvprintw(gridSize * 2 + 2, 0, "Press U to Undo, H for Hint, Arrow Keys/WASD to move, Q to Quit.");
        refresh();
        input = getch(); // Get user input

        bool validMove = false; // Flag to check if the input was valid
        bool moved = false; // Flag to check if the grid changed

        // Save the current state BEFORE making any move
        if (input == 'W' || input == 'w' || input == KEY_UP ||
            input == 'A' || input == 'a' || input == KEY_LEFT ||
            input == 'S' || input == 's' || input == KEY_DOWN ||
            input == 'D' || input == 'd' || input == KEY_RIGHT) {
            prevGrid = grid; // Save the current grid state
            prevScore = score; // Save the current score
            undoAvailable = true; // Undo becomes available after saving
        }

        // Handle user input and perform corresponding moves
        switch (input) {
            case 'W': case 'w': case KEY_UP:
                validMove = moveUp(grid, moved, score); break; // Move up
            case 'A': case 'a': case KEY_LEFT:
                validMove = moveLeft(grid, moved, score); break; // Move left
            case 'S': case 's': case KEY_DOWN:
                validMove = moveDown(grid, moved, score); break; // Move down
            case 'D': case 'd': case KEY_RIGHT:
                validMove = moveRight(grid, moved, score); break; // Move right
            case 'U': case 'u': // Handle Undo
                if (undoAvailable) {
                    grid = prevGrid; // Revert grid to previous state
                    score = prevScore; // Revert score to previous state
                    undoAvailable = false; // Undo is now unavailable
                } 
                refresh();
                continue; // Skip the rest of the loop after undo
            case 'H': case 'h': // Handle Hint
                currentHint = getBestMove(grid, score);
                if (currentHint == "None") {
                    currentHint = "No valid move found.";
                }
                continue; // Skip the rest of the loop after showing the hint
            case 'Q': case 'q':
                endwin(); // End ncurses mode
                return 0;
            default:
                mvprintw(gridSize * 2 + 7, 0, "Invalid input. Use Arrow Keys or WASD.");
                refresh();
                continue; // Skip further processing and wait for another input
        }

        // If the move was valid and the grid changed, add a new random tile
        if (validMove && moved) {
            addRandomTile(grid); // Add a new random tile after saving the state
            currentHint = "";  // Clear hint after a valid move
        }
    }

     // Update the best score if the current score is higher
    if (score > bestScore) {
        bestScore = score;
        saveBestScore(bestScore); // Save the new best score to the file
    }

    endwin(); // End ncurses mode and restore the terminal
    return 0;
}