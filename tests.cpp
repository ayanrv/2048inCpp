#include <iostream>
#include <vector>
#include "modele.hpp" // Include your original game logic header
#include "menu.hpp"   // For saveBestScore/loadBestScore

// Fonction pour afficher une grille.
// Paramètre : 
// "grid" : une matrice bidimensionnelle contenant les valeurs de la grille.
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Vérifie que la fonction `initializeGrid` initialise correctement la grille avec 2 tuiles non nulles.
// Critère de réussite : La grille contient exactement 2 cellules non nulles après l'initialisation
void testInitializeGrid() {
    std::cout << "Running testInitializeGrid...\n";
    std::vector<std::vector<int>> grid(4, std::vector<int>(4, 0)); 
    initializeGrid(grid);

    int nonZeroCount = 0;
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell != 0) nonZeroCount++;
        }
    }

    if (nonZeroCount == 2) {
        std::cout << "testInitializeGrid passed\n";
    } else {
        std::cout << "testInitializeGrid failed\n";
    }
}

// Teste la fonction `displayGrid` pour afficher correctement la grille et le score.
// Critère de réussite : Pas d'erreurs lors de l'exécution.
void testDisplayGrid() {
    std::cout << "Running testDisplayGrid...\n";
    try {
        std::vector<std::vector<int>> grid(4, std::vector<int>(4, 0));
        int score = 0;
        int bestScore = 1000; //just pour affichage
        displayGrid(grid, score, bestScore);
        std::cout << "testDisplayGrid passed )\n";
    } catch (...) {
        std::cout << "testDisplayGrid failed\n";
    }
}

// Teste l'ajout d'une tuile aléatoire sur une grille vide.
// Critère de réussite : La grille contient exactement une cellule non nulle après l'ajout.
void testAddRandomTile() {
    std::cout << "Running testAddRandomTile...\n";
    std::vector<std::vector<int>> grid(4, std::vector<int>(4, 0));
    addRandomTile(grid);

    int nonZeroCount = 0;
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell != 0) nonZeroCount++;
        }
    }

    if (nonZeroCount == 1) {
        std::cout << "testAddRandomTile passed\n";
    } else {
        std::cout << "testAddRandomTile failed\n";
    }
}

// Teste si la fonction `isGameOver` détecte correctement la fin du jeu.
// Cas de réussite : 
// - Renvoie `true` si aucune combinaison ni aucun déplacement n'est possible.
// - Renvoie `false` si un déplacement ou une combinaison reste possible.
void testIsGameOver() {
    std::cout << "Running testIsGameOver...\n";
    std::vector<std::vector<int>> grid = {
        {2, 4, 8, 16},
        {32, 64, 128, 256},
        {512, 1024, 2048, 4096},
        {2, 4, 8, 16}
    };

    if (isGameOver(grid)) {
        std::cout << "testIsGameOver (over state) passed\n";
    } else {
        std::cout << "testIsGameOver (over state) failed\n";
    }

    grid[3][3] = 8; // Make a valid move possible
    if (!isGameOver(grid)) {
        std::cout << "testIsGameOver (not over state) passed\n";
    } else {
        std::cout << "testIsGameOver (not over state) failed\n";
    }
}

// Teste le déplacement et la fusion d'une ligne de la grille.
// Cas de réussite : 
// - Les tuiles se combinent correctement et les scores sont mis à jour.
void testSlideAndMerge() {
    std::cout << "Running testSlideAndMerge...\n";

    std::vector<int> line = {2, 2, 4, 4};
    bool moved = false;
    int scoreDelta = 0;
    slideAndMerge(line, moved, scoreDelta);

    if (line == std::vector<int>{4, 8, 0, 0} && scoreDelta == 12) {
        std::cout << "testSlideAndMerge passed\n";
    } else {
        std::cout << "testSlideAndMerge failed\n";
    }
}

// Teste le déplacement et la fusion des tuiles lors d'un mouvement vers la gauche.
// Critère de réussite : La grille finale correspond à l'état attendu et le score est correct.
void testMoveLeft() {
    std::cout << "Running testMoveLeft...\n";
    std::vector<std::vector<int>> grid = {
        {2, 2, 0, 0},
        {4, 4, 4, 0},
        {8, 0, 8, 8},
        {16, 0, 0, 16}
    };


    std::cout << "Initial Grid:\n";
    printGrid(grid);

    int score = 0;
    bool moved = false;
    moveLeft(grid, moved, score);

    std::cout << "Grid After moveLeft:\n";
    printGrid(grid);

    std::vector<std::vector<int>> expected = {
        {4, 0, 0, 0},
        {8, 4, 0, 0},
        {16, 8, 0, 0},
        {32, 0, 0, 0}
    };

    if (grid == expected && score == 60) {
        std::cout << "testMoveLeft passed\n";
    } else {
        std::cout << "testMoveLeft failed\n";
    }
}

// Teste le déplacement et la fusion des tuiles lors d'un mouvement vers la droite.
void testMoveRight() {
    std::cout << "Running testMoveRight...\n";
    std::vector<std::vector<int>> grid = {
        {0, 0, 2, 2},
        {4, 0, 4, 4},
        {0, 8, 8, 8},
        {0, 16, 0, 16}
    };

    std::cout << "Initial Grid:\n";
    printGrid(grid);

    int score = 0;
    bool moved = false;
    moveRight(grid, moved, score);

    std::cout << "Grid After moveRight:\n";
    printGrid(grid);

    std::vector<std::vector<int>> expected = {
        {0, 0, 0, 4},
        {0, 0, 4, 8},
        {0, 0, 8, 16},
        {0, 0, 0, 32}
    };

    if (grid == expected && score == 60) {
        std::cout << "testMoveRight passed\n";
    } else {
        std::cout << "testMoveRight failed\n";
    }
}
// Teste le déplacement et la fusion des tuiles lors d'un mouvement vers le haut.
void testMoveUp() {
    std::cout << "Running testMoveUp...\n";
    std::vector<std::vector<int>> grid = {
        {2, 0, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    std::cout << "Initial Grid:\n";
    printGrid(grid);

    int score = 0;
    bool moved = false;
    moveUp(grid, moved, score);

    std::cout << "Grid After moveUp:\n";
    printGrid(grid);

    std::vector<std::vector<int>> expected = {
        {4, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    if (grid == expected && score == 4) {
        std::cout << "testMoveUp passed\n";
    } else {
        std::cout << "testMoveUp failed\n";
    }
}

// Teste le déplacement et la fusion des tuiles lors d'un mouvement vers le bas.
void testMoveDown() {
    std::cout << "Running testMoveDown...\n";
    std::vector<std::vector<int>> grid = {
        {2, 0, 0, 0},
        {2, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    std::cout << "Initial Grid:\n";
    printGrid(grid);

    int score = 0;
    bool moved = false;
    moveDown(grid, moved, score);

    std::cout << "Grid After moveDown:\n";
    printGrid(grid);

    std::vector<std::vector<int>> expected = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {4, 0, 0, 0}
    };

    if (grid == expected && score == 4) {
        std::cout << "testMoveDown passed\n";
    } else {
        std::cout << "testMoveDown failed\n";
    }
}

// Fonction principale pour exécuter tous les tests.
int main() {
    std::cout << "Running tests...\n";
    testInitializeGrid();
    testDisplayGrid();
    testAddRandomTile();
    testIsGameOver();
    testSlideAndMerge();
    testMoveLeft();
    testMoveRight();
    testMoveUp();
    testMoveDown();
    std::cout << "All tests completed.\n";
    return 0;
}
