# 🎮 2048 Game in C++ with AI

This project implements the classic **2048 game** in C++ with modular design and AI functionality. The game uses **PDCurses** for terminal-based UI and supports both manual gameplay and AI-driven automation.


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

# 🛠️ Key Components

## Game Mechanics
- **Tile Movement**:
  - Implements `moveUp`, `moveDown`, `moveLeft`, and `moveRight` functions.
- **Random Tile Addition**:
  - Adds a `2` (90%) or `4` (10%) tile to empty cells after every move.
- **Grid Display**:
  - Uses PDCurses to dynamically render the game grid with colorful tiles.

## AI Logic
- **Heuristic-based evaluation function**:
  1. **Score**: Prefers moves with higher immediate scores.
  2. **Empty Tiles**: Prioritizes moves that free up space.
  3. **Monotonicity**: Encourages tile ordering for easier merges.
  4. **Merge Potential**: Favors moves with high merging opportunities.
- **Three-move prediction**:
  - Evaluates up to three moves ahead to select the most optimal path.

---

# 📂 Project Structure

| File             | Description                                                |
|------------------ |-----------------------------------------------------------|
| `2048.cpp`       | Main file for the classic game, including game loops.      |
| `ai_player.cpp`  | Main file for the AI-driven autonomous mode.               |
| `ai.cpp`         | Implements the AI logic, including heuristic evaluation.   |
| `menu.cpp`       | Handles the interactive menu and game setup.               |
| `modele.cpp`     | Core game mechanics: tile movement, merging, and scoring.  |
| `menu.hpp`       | Header file for menu-related logic.                        |
| `modele.hpp`     | Header file for core game mechanics.                       |
| `ai.hpp`         | Header file for AI logic.                                  |

---

## 📜 How to Compile and Run

### Prerequisites
- **`g++`** (GNU Compiler).
- **PDCurses** library installed:
  - Download from [PDCurses GitHub](https://github.com/wmcbrine/PDCurses).

### Compilation Commands

### Prerequisites
1. **`g++`** (GNU Compiler).
2. **PDCurses** library:
   - Download and set up PDCurses from [PDCurses GitHub](https://github.com/wmcbrine/PDCurses).
   - Add the `PDCurses` include and library paths to your system.

---

### Compilation Instructions

#### Classic 2048 Game
To build the classic game:

g++ 2048.cpp modele.cpp menu.cpp ai.cpp -o 2048 -I"C:/PDCurses-master" -L"C:/PDCurses-master/wincon" -lpdcurses
---
#### AI-Powered Version
To build AI-Powered autonomous player:

g++ ai_player.cpp modele.cpp menu.cpp ai.cpp -o ai_player -I"C:/PDCurses-master" -L"C:/PDCurses-master/wincon" -lpdcurses
---
### Running the game
1. Run the Classic Game:
    ./2048
2. Run the AI Mode:
    ./ai_player

---

## ❤️ Developed For
This project was developed as part of the **Université Paris-Saclay Programmation Imperative C++ Course**.

---

