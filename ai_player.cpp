#include "modele.hpp"   // Game logic functions
#include "ai.hpp"       // AI decision-making
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <curses.h>     // For visual display

// Function declaration for the AI
std::string getBestMove(const std::vector<std::vector<int>>& grid, int currentScore);
int evaluateGrid(const std::vector<std::vector<int>>& grid);


// Main function to run the AI-powered game
int main() {
    int gridSize = 5;         // Game grid size
    int score = 0;            // Current game score
    int bestScore = loadBestScore(); // Load the best score from the file
    bool moved;               // Tracks if the move was successful

    // Initialize the game grid
    std::vector<std::vector<int>> grid(gridSize, std::vector<int>(gridSize, 0));

    // Seed the random number generator
    std::srand(std::time(0));

    // Initialize ncurses screen
    initscr();             // Start ncurses mode
    noecho();              // Disable echoing input
    cbreak();              // Disable line buffering
    keypad(stdscr, TRUE);  // Enable special key input
    initializeColors();    // Initialize game colors

    // Add two starting tiles
    initializeGrid(grid);

    // Run the AI game loop
    while (true) {
        // Clear screen and display the current game state
        clear();
        displayGrid(grid, score, bestScore);  // Display the game grid

        // Check if the game is over
        if (isGameOver(grid)) {
            mvprintw(gridSize * 2 + 5, 0, "Game Over! Final Score: %d", score);
            mvprintw(gridSize * 2 + 6, 0, "Press any key to exit...");
            refresh();
            getch();  // Wait for key press before exiting
            break;
        }

        // Get the best move from the AI
        std::string bestMove = getBestMove(grid, score);
        mvprintw(gridSize * 2 + 7, 0, "AI's Best Move: %s", bestMove.c_str());
        refresh();

        // Apply the best move based on AI's decision
        if (bestMove == "Up") moveUp(grid, moved, score);
        else if (bestMove == "Down") moveDown(grid, moved, score);
        else if (bestMove == "Left") moveLeft(grid, moved, score);
        else if (bestMove == "Right") moveRight(grid, moved, score);
        else {
            mvprintw(gridSize * 2 + 8, 0, "No valid moves! Ending game.");
            refresh();
            getch();
            break;
        }

        // Add a random tile after a valid move
        if (moved) addRandomTile(grid);

        // Pause for animation effect (adjust if needed)
        napms(300);  // 300 ms delay for visibility
    }

    // End ncurses mode and restore terminal
    endwin();
    return 0;
}
