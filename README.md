# 🎮 2048 Game in C++ with AI

This project implements the classic **2048 game** in C++ with modular design and AI functionality. The game uses **PDCurses** for terminal-based UI and supports both manual gameplay and AI-driven automation.

---

## 📂 Project Overview

This repository contains:
- A **classic 2048 game** where you can manually play by sliding tiles.
- An **AI player** that predicts moves up to three steps ahead to aim for the highest score.
- Modular design for easy understanding and maintainability.

---

## 🚀 Features

### 🎮 Classic Gameplay
- **Sliding Tiles**: Use `W`, `A`, `S`, `D` or arrow keys to move tiles.
- **Undo Support**: Undo the last move for better strategy.
- **Dynamic Grid Size**: Play with grids of size 4x4, 5x5, or 6x6.
- **Hints**: Use AI to suggest the best move for your current state.
- **Score Tracking**: Displays the current and best scores.

### 🤖 AI Mode
- Predicts up to **three steps ahead** to evaluate the best moves.
- Heuristic evaluation based on:
  - **Score Maximization**: Prioritizes moves that yield the highest score.
  - **Empty Tiles**: Keeps more open spaces for survivability.
  - **Monotonicity**: Encourages a smooth tile arrangement for easier merging.
  - **Merge Potential**: Favors moves that create larger tiles.
- Fully autonomous gameplay.

---

## 📜 How to Compile and Run

### Prerequisites
- **`g++`** (GNU Compiler).
- **PDCurses** library installed:
  - Download from [PDCurses GitHub](https://github.com/wmcbrine/PDCurses).

### Compilation Commands

#### Compile the Classic 2048 Game
```bash
g++ 2048.cpp modele.cpp menu.cpp ai.cpp -o 2048 -I"C:/PDCurses-master" -L"C:/PDCurses-master/wincon" -lpdcurses

#### Compile the AI Player
```bash
g++ ai_player.cpp modele.cpp menu.cpp ai.cpp -o ai_player -I"C:/PDCurses-master" -L"C:/PDCurses-master/wincon" -lpdcurses

## Running the Game
1. Run the classic game:
```bash
./2048

2. Run the AI mode:
```bash
./ai_player

### 📂 Project Structure
File :	Description
2048.cpp : Main file for the classic game, including game loops.
ai_player.cpp	: Main file for the AI-driven autonomous mode.
ai.cpp : Implements the AI logic, including heuristic evaluation.
menu.cpp : Handles the interactive menu and game setup.
modele.cpp : Core game mechanics (tile movement, merging, etc.).
menu.hpp modele.hpp ai.hpp : Header files for the respective modules.

### 🛠️ Key Components
#### Game Mechanics
- Tile Movement: Implements moveUp, moveDown, moveLeft, and moveRight functions.
- Random Tile Addition: Adds a 2 (90%) or 4 (10%) tile to empty cells after every move.
- Grid Display: Uses PDCurses to render the game grid dynamically.
#### AI Logic
- Uses a heuristic-based evaluation function:
    1. Score: Prefers moves with higher immediate scores.
    2. Empty Tiles: Prioritizes moves that free up space.
    3. Monotonicity: Encourages tile ordering for easier merges.
    4. Merge Potential: Favors moves with high merging opportunities.
- Predicts up to three moves ahead to select the most optimal path.

### 🖥️ Sample Outputs
Classic Game
+----+----+----+----+
|    |    |    |    |
+----+----+----+----+
|    |    |    |    |
+----+----+----+----+
|    |    |    |    |
+----+----+----+----+
|    |    |    |    |
+----+----+----+----+

Score: 0
Best Score: 1024

Enter move (W: Up, A: Left, S: Down, D: Right, H: Hint, U: Undo, Q: Quit):

Developed with ❤️ for the Université Paris-Saclay Programmation Imperative C++ Course.