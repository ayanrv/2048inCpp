
# 🎮 2048 Game in C++

Welcome to the **2048 Game**, implemented entirely in C++! This console-based game brings the addictive puzzle gameplay of **2048** to your terminal. Merge tiles, strategize, and aim for the **2048 tile** to win!

---

## 🚀 Features

- **Classic Gameplay**: Slide and merge tiles to create higher values.
- **Random Tile Generation**: Adds a touch of unpredictability with new tiles appearing after every valid move.
- **Game Over Detection**: Ends the game when no valid moves are left.
- **Clean, Modular Code**: Each functionality is implemented as a separate, reusable function.
- **Simple and Intuitive Interface**: Play using `W`, `A`, `S`, and `D` for directions. Player can see their score, it updates when the merge occurs.

---

## 🎯 How to Play

1. **Compile the Code**:
   ```bash
   g++ Project.cpp -o 2048
   ```
2. **Run the Game**:
   ```bash
   ./2048
   ```
3. **Controls**:
   - **W**: Move Up
   - **A**: Move Left
   - **S**: Move Down
   - **D**: Move Right

4. **Goal**: Merge tiles to reach the **2048** tile.

---

## 🛠️ Code Overview

### 🔧 Constants
- **`GRID_SIZE`**: Sets the grid size to 4x4.

### 🌀 Initialization
- **`initializeGrid(std::vector<std::vector<int>>& grid)`**:
  Fills the grid with two random tiles (either `2` or `4`).

### 🖥️ Display
- **`displayGrid(const std::vector<std::vector<int>>& grid, int score)`**:
  Prints the grid in a clean and formatted layout.

### 🎲 Random Tile Generation
- **`addRandomTile(std::vector<std::vector<int>>& grid)`**:
  Adds a random tile (either `2` or `4`) to an empty cell.

### 🕹️ Game Logic
- **`isGameOver(const std::vector<std::vector<int>>& grid)`**:
  Checks if the player has any valid moves left.
- **`slideAndMerge(std::vector<int>& line, bool& moved, int& scoreDelta)`**:
  Slides and merges a single row or column. Tracks if any changes occurred.

### 🚦 Movement Functions
Moves tiles in the specified direction and merges them if possible:
- **`moveLeft(std::vector<std::vector<int>>& grid, bool& moved, int& score)`**
- **`moveRight(std::vector<std::vector<int>>& grid, bool& moved, int& score)`**
- **`moveUp(std::vector<std::vector<int>>& grid, bool& moved, int& score)`**
- **`moveDown(std::vector<std::vector<int>>& grid, bool& moved, int& score)`**

---

## 📋 Sample Output

Here’s how the grid appears during gameplay:

```
+----+----+----+----+
|    |    |    |    |
+----+----+----+----+
|    |    |    |    |
+----+----+----+----+
|    |    |    |    |
+----+----+----+----+
|    |    |    |    |
+----+----+----+----+

Enter move (W: Up, A: Left, S: Down, D: Right):
Score:
```

---

## 🔮 Future Enhancements

- **Score Tracking**: Display a score for the player’s performance.
- **Graphical Interface**: 
- **Save & Load**: Allow saving and loading game states.
- **Customizable Grid Size**: 
- **Undo Moves**: Add an undo feature for the last move.
- **Use Ncurses library**: 

---

## 👨‍💻 Author

Created with ❤️ for Programmation Imperative on C++ course in Universite Paris-Saclay. 

---
