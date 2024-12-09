#include "ai.hpp"
#include "modele.hpp"  // Include game logic functions
#include <vector>
#include <string>
#include <climits>

/////////////////////////////////////////////////////////////////////////////////
// Fonction: evaluateGrid()
// Description: Évalue la grille actuelle du jeu en utilisant une heuristique pondérée qui
//              prend en compte le score, les tuiles vides, la monotonie et le potentiel de fusion.
//@param:
//   - grid: l'etat actuel du plateau de jeu sous forme de vecteur 2d 
// @returns: Un entier représentant le score d'évaluation de la grille.
/////////////////////////////////////////////////////////////////////////////////
int evaluateGrid(const std::vector<std::vector<int>>& grid) {
    int emptyTiles = 0;      // nombre de tuile nulles
    int score = 0;           // somme totale des valeurs des tuiles (score du jeu)
    int monotonicity = 0;    // suivi de la regularité/ordre des tuiles
    int mergePotential = 0;  // suivi des tuiles fusionnables
    
    //parcourt tout le plateau pour calculer lescomposants de l'evaluation
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == 0) emptyTiles++;  // Count les tuiles nulles
            score += grid[i][j];               // ajoute la valeur de la tuile au score
        }
    }

    // Calcule monotonie des lignes et des colonnes
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size() - 1; ++j) {
            // verification de la monotonie sur les lignes
            if (grid[i][j] >= grid[i][j + 1]) monotonicity++;
            
            // verification de la monotonie des colonnes
            if (grid[j][i] >= grid[j + 1][i]) monotonicity++;
        }
    }

   // Comptage du potentiel de fusion adjacent pour les lignes et les colonnes
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size() - 1; ++j) {
            // Vérification des fusions horizontales (de gauche à droite)
            if (grid[i][j] == grid[i][j + 1]) mergePotential++;
            
            // Vérification des fusions verticales (de haut en bas)
            if (grid[j][i] == grid[j + 1][i]) mergePotential++;
        }
    }

    // Retourne le score d'évaluation pondéré
    // Poids :
    // - Tuiles vides (200) : Garde plus de mouvements disponibles
    // - Monotonie (50) : Garde les tuiles ordonnées
    // - Potentiel de fusion (100) : Encourage les fusions
    return score + emptyTiles * 200 + monotonicity * 50 + mergePotential * 100;
}

/////////////////////////////////////////////////////////////////////////////////
// Fonction : getBestMove
// Description : Détermine le meilleur mouvement en utilisant une prévision à trois niveaux 
//              en évaluant tous les mouvements possibles et en sélectionnant le chemin le plus optimal.
// @param :
//   - grid : La grille actuelle du jeu sous forme de vecteur 2D d'entiers.
//   - currentScore : Le score actuel du jeu.
// @return : Une chaîne de caractères représentant le meilleur mouvement ("Up", "Down", "Left", "Right").
/////////////////////////////////////////////////////////////////////////////////
std::string getBestMove(const std::vector<std::vector<int>>& grid, int currentScore) {
    int maxEvaluation = INT_MIN;  // Stocke le meilleur score d'évaluation trouvé
    std::string bestMove = "None";  // Suivi du meilleur mouvement basé sur l'évaluation

    // Grilles temporaires pour simuler les mouvements à différents niveaux
    std::vector<std::vector<int>> tempGrid, futureGrid, thirdGrid;
    int score, futureScore, thirdScore;  // Suivi des scores après les mouvements simulés
    bool moved, futureMoved, thirdMoved;  // Suivi si un mouvement a réussi

    // Évaluation du premier niveau de mouvement
    for (int move = 0; move < 4; ++move) {
        tempGrid = grid;  // Réinitialise la grille à l'état original
        score = currentScore;
        moved = false;

        // Simulation du premier mouvement
        switch (move) {
            case 0: moveUp(tempGrid, moved, score); break;      // Simule "Haut"
            case 1: moveDown(tempGrid, moved, score); break;    // Simule "Bas"
            case 2: moveLeft(tempGrid, moved, score); break;    // Simule "Gauche"
            case 3: moveRight(tempGrid, moved, score); break;   // Simule "Droite"
        }

        if (!moved) continue;  // Passe au mouvement suivant si aucune tuile n'a bougé

        // Évaluation du deuxième niveau de mouvement
        for (int nextMove = 0; nextMove < 4; ++nextMove) {
            futureGrid = tempGrid;  // Réinitialise la grille après le premier mouvement
            futureScore = score;    // Réinitialise le score après le premier mouvement
            futureMoved = false;

            // Simulation du deuxième mouvement
            switch (nextMove) {
                case 0: moveUp(futureGrid, futureMoved, futureScore); break;   // Simule "Haut"
                case 1: moveDown(futureGrid, futureMoved, futureScore); break; // Simule "Bas"
                case 2: moveLeft(futureGrid, futureMoved, futureScore); break; // Simule "Gauche"
                case 3: moveRight(futureGrid, futureMoved, futureScore); break;// Simule "Droite"
            }

            if (!futureMoved) continue;  // Passe si aucune tuile n'a bougé dans le deuxième mouvement

            // Évaluation du troisième niveau de mouvement
            for (int lastMove = 0; lastMove < 4; ++lastMove) {
                thirdGrid = futureGrid;  // Réinitialise la grille après le deuxième mouvement
                thirdScore = futureScore;  // Réinitialise le score après le deuxième mouvement
                thirdMoved = false;

                // Simulation du troisième mouvement
                switch (lastMove) {
                    case 0: moveUp(thirdGrid, thirdMoved, thirdScore); break;   // Simule "Haut"
                    case 1: moveDown(thirdGrid, thirdMoved, thirdScore); break; // Simule "Bas"
                    case 2: moveLeft(thirdGrid, thirdMoved, thirdScore); break; // Simule "Gauche"
                    case 3: moveRight(thirdGrid, thirdMoved, thirdScore); break;// Simule "Droite"
                }

                if (!thirdMoved) continue;  // Passe si aucune tuile n'a bougé dans le troisième mouvement

                // Évalue la grille après trois mouvements
                int evaluation = evaluateGrid(thirdGrid);

                // Met à jour le meilleur mouvement si ce chemin est meilleur
                if (evaluation > maxEvaluation) {
                    maxEvaluation = evaluation;
                    switch (move) {
                        case 0: bestMove = "Up"; break;
                        case 1: bestMove = "Down"; break;
                        case 2: bestMove = "Left"; break;
                        case 3: bestMove = "Right"; break;
                    }
                }
            }
        }
    }

    // Retourne le meilleur mouvement évalué
    return bestMove;
}