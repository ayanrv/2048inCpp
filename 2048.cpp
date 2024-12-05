#include "modele.hpp"
#include <curses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

// Main function to run the game
int main() {
    std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 0)); // Create a 4x4 grid initialized with zeros
    int score = 0; // Initialize the game score
    int input; // Use int instead of char for user input

    std::srand(std::time(0)); // Seed random number generator for random tile placement

    // Initialize ncurses screen
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); // Enable arrow key input

    initializeColors(); // Initialize color pairs for the game
    initializeGrid(grid); // Add two random tiles to start the game

    // Main game loop
    while (true) {
        clear(); // Clear the screen to prepare for drawing the grid
        displayGrid(grid, score); // Render the grid and display the score

        // Check if the game is over
        if (isGameOver(grid)) {
            mvprintw(GRID_SIZE * 2 + 2, 0, "Game Over! No more valid moves!"); // Game over message
            mvprintw(GRID_SIZE * 2 + 3, 0, "Press any key to exit...");
            refresh(); // Refresh the screen to show game-over messages
            getch(); // Wait for user input to acknowledge the game over
            break; // Exit the main game loop
        }

        // Prompt the user for input
        mvprintw(GRID_SIZE * 2 + 1, 0, "Use Arrow Keys or WASD for movement. Press Q to Quit.");
        refresh(); // Display the prompt
        input = getch(); // Capture user input

        bool validMove = false; // Flag to check if the input was valid
        bool moved = false; // Flag to check if the grid changed

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
        case 'Q': case 'q':
            endwin(); // End ncurses mode and restore the terminal
            return 0; // Exit the game
        default:
            mvprintw(GRID_SIZE * 2 + 4, 0, "Invalid input. Use Arrow Keys or WASD.");
            refresh();
            continue; // Skip further processing and wait for another input
        }

        // If the move was valid and the grid changed, add a new random tile
        if (validMove && moved) {
            addRandomTile(grid);
        }
    }

    endwin(); // End ncurses mode and restore the terminal
    return 0;
}