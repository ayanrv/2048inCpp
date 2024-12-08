#ifndef MODELE_HPP
#define MODELE_HPP

#include <vector>
#include <string>

// Function prototypes
void initializeGrid(std::vector<std::vector<int>>& grid);
void displayGrid(const std::vector<std::vector<int>>& grid, int score, int bestScore);
void addRandomTile(std::vector<std::vector<int>>& grid);
bool isGameOver(const std::vector<std::vector<int>>& grid);
bool moveLeft(std::vector<std::vector<int>>& grid, bool& moved, int& score);
bool moveRight(std::vector<std::vector<int>>& grid, bool& moved, int& score);
bool moveUp(std::vector<std::vector<int>>& grid, bool& moved, int& score);
bool moveDown(std::vector<std::vector<int>>& grid, bool& moved, int& score);
bool slideAndMerge(std::vector<int>& line, bool& moved, int& scoreDelta);
void initializeColors();
int getColorPairIndex(int value);

// Function declarations for best score management
void saveBestScore(int bestScore);  // Save the best score to a file
int loadBestScore();               // Load the best score from a file


#endif