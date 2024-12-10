#include "modele.hpp"   // Game logic functions
#include "ai.hpp"       // AI decision-making
<<<<<<< Updated upstream
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
    int gridSize = 4;         // Game grid size
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
    nodelay(stdscr, TRUE); // Non-blocking input
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

        // Check for user input to quit
        int ch = getch();  // Non-blocking input
        if (ch == 'q' || ch == 'Q') {
            mvprintw(gridSize * 2 + 5, 0, "Quitting game... Goodbye!");
            refresh();
            napms(1000);  // Wait for 1 second before exiting
            break;
        }

        // Get the best move from the AI
        std::string bestMove = getBestMove(grid, score);
        mvprintw(gridSize * 2 + 7, 0, "AI's Best Move: %s", bestMove.c_str());
        refresh();

        // Apply the best move based on AI's decision
=======
#include <vector>       // For dynamic 2D grid representation
#include <iostream>     // For debugging and output (if needed)
#include <cstdlib>      // For random number generation
#include <ctime>        // For seeding the random generator
#include <curses.h>     // For graphical display using ncurses

// Main function to run the AI-powered game
int main() {
    int gridSize = 4;         // Define the game grid size
    int score = 0;            // Initialize current game score
    int bestScore = loadBestScore(); // Load the best score from a saved file
    bool moved;               // Track whether a move was successful

    // Initialize the game grid as a 2D vector filled with zeros
    std::vector<std::vector<int>> grid(gridSize, std::vector<int>(gridSize, 0));

    // Seed the random number generator based on current time
    std::srand(std::time(0));

    // Initialize ncurses screen for graphical display
    initscr();              // Start ncurses mode
    noecho();               // Disable input echoing
    cbreak();               // Disable line buffering
    keypad(stdscr, TRUE);   // Enable function keys and arrow keys
    initializeColors();     // Initialize game tile colors

    // Add two random tiles to start the game
    initializeGrid(grid);

    // Main AI game loop
    while (true) {
        clear();                        // Clear screen for next display
        displayGrid(grid, score, bestScore);  // Display the current game state

        // Show game info and instructions
        mvprintw(gridSize * 2 + 3, 0, "Press Q to quit");
        mvprintw(gridSize * 2 + 4, 0, "Score: %d", score);
        mvprintw(gridSize * 2 + 5, 0, "Best Score: %d", bestScore);

        timeout(0);         // Non-blocking input check
        int ch = getch();   // Get player input
        if (ch == 'q' || ch == 'Q') {  // Check for quit command
            break;          // Exit the game loop
        }

        if (isGameOver(grid)) {  // Check if the game is over
            mvprintw(gridSize * 2 + 6, 0, "Game Over! No more valid moves.");
            refresh();      // Update the display
            break;          // Exit the game loop
        }

        // Get the best move from the AI decision-making algorithm
        std::string bestMove = getBestMove(grid, score);
        mvprintw(gridSize * 2 + 7, 0, "AI's Best Move: %s", bestMove.c_str());
        refresh();          // Update the screen with AI's decision

        // Perform the AI's suggested move
>>>>>>> Stashed changes
        if (bestMove == "Up") moveUp(grid, moved, score);
        else if (bestMove == "Down") moveDown(grid, moved, score);
        else if (bestMove == "Left") moveLeft(grid, moved, score);
        else if (bestMove == "Right") moveRight(grid, moved, score);
<<<<<<< Updated upstream
        else {
            mvprintw(gridSize * 2 + 8, 0, "No valid moves! Ending game.");
            refresh();
            getch();
            break;
        }

        mvprintw(gridSize * 2 + 2, 0, "Press Q to Quit.");
        refresh();

        // Add a random tile after a valid move
        if (moved) addRandomTile(grid);

        // Pause for animation effect (adjust if needed)
        napms(300);  // 300 ms delay for visibility
    }

    // End ncurses mode and restore terminal
    endwin();
    return 0;
=======
        else {  // No valid moves left
            mvprintw(gridSize * 2 + 8, 0, "No valid moves! Ending game.");
            refresh();      // Update the display
            break;          // Exit the game loop
        }

        if (moved) addRandomTile(grid); // Add a random tile if the move was successful

        napms(30);          // Delay for smoother animation (300 ms)
    }

    // Final Summary Display
    clear();   // Clear screen for summary display
    mvprintw(0, 0, "==== Final Game State Summary ====");
    displayGrid(grid, score, bestScore);  // Show the final game state
    mvprintw(gridSize * 2 + 3, 0, "Final Score: %d", score);  // Display final score
    mvprintw(gridSize * 2 + 4, 0, "Best Score Achieved: %d", bestScore);  // Show best score
    mvprintw(gridSize * 2 + 5, 0, "Press Q to exit...");  // Prompt to quit the game

    // Wait for user confirmation to exit the game
    while (true) {
        int ch = getch();  // Wait for key press
        if (ch == 'q' || ch == 'Q') break;  // Exit if 'Q' or 'q' is pressed
    }

    endwin();  // Close ncurses screen and restore the terminal
    return 0;  // End the program
>>>>>>> Stashed changes
}
