#include "modele.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <curses.h>
#include <iostream>
#include <vector>

// Initialise les couleurs pour l'affichage dans une interface ncurses.
 // Cette fonction active les fonctionnalités de couleurs de la bibliothèque ncurses
 // et configure des paires de couleurs pour différents éléments graphiques. Les 
 // couleurs définies incluent des couleurs de fond pour des tuiles et des bordures.
void initializeColors() {
    start_color();              // Appelle `start_color()` pour activer les couleurs dans ncurses
    use_default_colors();       // pour permettre l'utilisation des couleurs par défaut du terminal comme base.

    // tableau de couleur
    int tileColors[] = {COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_CYAN,
                        COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE};

    // Creer des pairs de couleurs : blanc pour le texte et une autre couleur pour le fond
    for (int i = 0; i < 7; ++i) {
        init_pair(i + 1, COLOR_WHITE, tileColors[i]); 
    }

    
    init_pair(8, COLOR_YELLOW, -1);     // pair pour bordures horizontales
    init_pair(9, COLOR_YELLOW, -1);     // pair pour bordures verticales
}

// Roulette pour donner des couleurs aux chiffres 
// @param la valeur du chiffres
// @return une couleur par rapport a son chiffre 
int getColorPairIndex(int value) {
    if (value == 0) return -1;  // aucune couleur quand nul
    int colorCount = 7;         // nombres totales de couleurs definies
    int index = 0;              // commence avec la premiere paire de couleur

    // Determine the index based on the power of 2
    while (value > 1) {
        value /= 2;
        ++index;
    }

    //roulette de couleur
    return (index - 1) % colorCount + 1; 
}

// Debut de jeu: initialise le plaeau 
//@param notre plateau de jeu
//@return notre plateau avec deux tuiles aleatoirement placer sur le plateau 
void initializeGrid(std::vector<std::vector<int>>& grid) {
    addRandomTile(grid); 
    addRandomTile(grid); 
}

// Affichage du tableau 
//@param notre vecteur 2d et le score du jeu
//@return le plateau affichier avec les bonnes couleurs, le score et les indices pour jouer
void displayGrid(const std::vector<std::vector<int>>& grid, int score, int bestScore) {
    clear();   // efface l'ecran avant de reafficher un plateau 
    const std::string horizontalBorder = "+-----"; // format de bordures pour les tuiles

    //passe par toutes les cases du tableau 
    for (int i = 0; i < grid.size(); ++i) {
        // bordures en jaune 
        attron(COLOR_PAIR(8)); 
        for (int j = 0; j < grid.size(); ++j) {
            mvprintw(i * 2, j * 6, "+-----"); // affiche la bordures sur l'ecran
        }
        mvprintw(i * 2, grid.size() * 6, "+"); // pour clore la case
        attroff(COLOR_PAIR(8)); // eteint la fonction de couleur pour les bordures

        
        for (int j = 0; j < grid[i].size(); ++j) {
            int value = grid[i][j]; // prend la valeur de la case
            int colorPair = getColorPairIndex(value); // lui attribue une pair de couleur 

            // Afficher la bordure verticale (côté gauche de la cellule)
            attron(COLOR_PAIR(9));           // Active le jaune pour les bordures verticales
            mvprintw(i * 2 + 1, j * 6, "|"); // Affiche la bordure verticale
            attroff(COLOR_PAIR(9));          // Désactive le jaune pour les bordures verticales

           // affiche la valeur de la cellule ou laisse vide si la valeur est 0
            if (value == 0) {
                mvprintw(i * 2 + 1, j * 6 + 1, "     "); // affiche un espace vide pour les cellules vides
            } else {
                attron(COLOR_PAIR(colorPair)); // Active la paire de couleurs correspondant à la valeur
                mvprintw(i * 2 + 1, j * 6 + 1, " %4d", value); // affiche la valeur de la cellule, alignée à droite sur 5 espaces
                attroff(COLOR_PAIR(colorPair)); // Désactive la paire de couleurs
            }           

        }

        // afiche la bordure verticale finale à la fin de la ligne
        attron(COLOR_PAIR(9)); // Active le jaune pour les bordures verticales
        mvprintw(i * 2 + 1, grid.size() * 6, "|"); // affiche la bordure verticale finale
        attroff(COLOR_PAIR(9)); // Désactive le jaune pour les bordures verticales

    }

    // Affiche la bordure horizontale finale en bas de la grille
    attron(COLOR_PAIR(8)); // Active la paire de couleurs pour les bordures horizontales
    for (int j = 0; j < grid.size(); ++j) {
        mvprintw(grid.size() * 2, j * 6, "+-----"); // Affiche la bordure horizontale pour chaque cellule
    }
    mvprintw(grid.size() * 2, grid.size() * 6, "+"); // Affiche le "+" final à la fin de la dernière ligne
    attroff(COLOR_PAIR(8)); // Désactive la paire de couleurs pour les bordures horizontales

    // Affiche le score et le meilleur score en dessous de la grille
    mvprintw(grid.size() * 2 + 4, 0, "Score: %d", score); //  Affiche le score actuel
    mvprintw(grid.size() * 2 + 5, 0, "Best Score: %d", bestScore); // Affiche le meilleur score
    refresh(); // Rafraîchit l'écran pour afficher tous les changements
}


// a chaque partie rajoute une tuile de valeur 2 ou 4 quand possible
//@param notre plateau actuel
//@return notre plateau avec deux additions de tuile si possible
void addRandomTile(std::vector<std::vector<int>>& grid) {
    std::vector<std::pair<int, int>> emptyCells; // List des cellules nulles

    // trouve toutes les cellules nulles sur le plateau
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid.size(); ++j) {
            if (grid[i][j] == 0) {
                emptyCells.emplace_back(i, j); // ajoute les cellules trouver a la liste
            }
        }
    }

    // si on n'en trouve pas, ne rien faire 
    if (emptyCells.empty()) return;

    // Selectionne une cellule de la liste et y ajoute un 2 ou 4
    int randomIndex = std::rand() % emptyCells.size(); //genere un index aleatoire 
    int value = (std::rand() % 10 < 9) ? 2 : 4; // 90% chance poutr 2, 10% pour 4
    grid[emptyCells[randomIndex].first][emptyCells[randomIndex].second] = value; //remplace la valeur de la cellule par la nouvelle valeur
}

// regarde si il est possible de continuer a jouer 
//@param notre plateau
//@return True si aucun mouvement nest possible 
bool isGameOver(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < grid.size(); ++i) { // parcourt les lignes
        for (int j = 0; j < grid.size(); ++j) { // parcourt les colonnes
            if (grid[i][j] == 0) return false; // tuile vide: le jeu n'est pas fini
            if (i < grid.size() - 1 && grid[i][j] == grid[i + 1][j]) return false; // fusion verticale possible
            if (j < grid.size() - 1 && grid[i][j] == grid[i][j + 1]) return false; // fusion horizontale possible
        }
    }
    return true; // aucun mouvement possible, jeu fini
}

// fonction utilitaire pour fusionnement et mouvement & regarde si il y a eu un changement sur le plateau apres que le joueur clique sur une touche 
//@param notre plateau, un bool pour voir si il y a eu mouvement, et le score 
//@return true si la ligne a ete modifie (glissement ou fusion)
bool slideAndMerge(std::vector<int>& line, bool& moved, int& scoreDelta) {
    bool lineChanged = false; // nouvelle bool pour sivre les changements 
    int size = line.size();
    // fait glisser les valeurs non nulles vers la gauche 
    std::vector<int> newLine(size, 0);
    int index = 0;
    for (int value : line) {
        if (value != 0) {
            newLine[index++] = value;
        }
    }

    if (newLine != line) {  // verifie si la ligne à bien changé
        lineChanged = true;
    }

    // fusionne les tuiles adjacentes
    for (int i = 0; i < size - 1; ++i) {
        if (newLine[i] != 0 && newLine[i] == newLine[i + 1]) {
            newLine[i] *= 2;     // double la valeur 
            scoreDelta += newLine[i]; //mis à jour du score 
            newLine[i + 1] = 0;  // efface la cellule fusionnée
            lineChanged = true; // precise le changement pour le bool
            i++; //sauter la prochaine tuile pour eviter deux fusions
        }
    }

    // refait glisser apres la fusion
    index = 0;
    for (int value : newLine) {
        if (value != 0) {
            line[index++] = value;
        }
    }
    while (index < size) {   // remplie les cellules restantes par 0
        line[index++] = 0;
    }

    if (lineChanged) {  // mise à jour du bool
        moved = true;
    }

     // verifie si la ligne à changé
    if (line != newLine) {
        moved = true;
    }


    return lineChanged; 
}

// Mouvement vers la gauche 
//@param notre plateau et le score 
//@return un plateau ou tout les mouvement vers la gauche on etait fait si possible et avec un score changé
bool moveLeft(std::vector<std::vector<int>>& grid, bool& moved, int& score) {
    moved = false;
    int scoreDelta = 0;
    for (auto& row : grid) {
        bool rowMoved = false;
        slideAndMerge(row, rowMoved, scoreDelta);  
        if (rowMoved) {
            moved = true;  // mets à jour le bool si la ligne à changé
        }
    }
    score += scoreDelta; // mise à jour du score
    return moved;
}
// Mouvement vers la droite
//@param notre plateau et le score 
//@return un plateau ou tout les mouvement vers la droite on etait fait si possible et avec un score changé
bool moveRight(std::vector<std::vector<int>>& grid, bool& moved, int& score) {
    moved = false;
    int scoreDelta = 0;
    for (auto& row : grid) {
        std::reverse(row.begin(), row.end());
        bool rowMoved = false;
        slideAndMerge(row, rowMoved, scoreDelta);  
        if (rowMoved) {
            moved = true;  // mets à jour le bool si la ligne à changé
        }
        std::reverse(row.begin(), row.end());
    }
    score += scoreDelta;
    return moved;
}
// Mouvement vers le haut 
//@param notre plateau et le score 
//@return un plateau ou tout les mouvement vers le haut on etait effectué si possible avec le score mise a jour
bool moveUp(std::vector<std::vector<int>>& grid, bool& moved, int& score) {
    moved = false;
    int scoreDelta = 0;
    for (int col = 0; col < grid.size(); ++col) {
        std::vector<int> column(grid.size());
        for (int row = 0; row < grid.size(); ++row) {
            column[row] = grid[row][col];
        }
        bool colMoved = false;
        slideAndMerge(column, colMoved, scoreDelta); 
        if (colMoved) {
            moved = true; 
        }
        for (int row = 0; row < grid.size(); ++row) {
            grid[row][col] = column[row];
        }
    }
    score += scoreDelta; // mise à jour du score
    return moved;
}
// Mouvement vers le bas
//@param notre plateau et le score 
//@return un plateau ou tout les mouvement vers le bas on etait effectuer si possible avec un score mise a jour
bool moveDown(std::vector<std::vector<int>>& grid, bool& moved, int& score) {
    moved = false;
    int scoreDelta = 0;
    for (int col = 0; col < grid.size(); ++col) {
        std::vector<int> column(grid.size());
        for (int row = 0; row < grid.size(); ++row) {
            column[row] = grid[grid.size() - 1 - row][col]; //utilise l'inverse
        }
        bool colMoved = false;
        slideAndMerge(column, colMoved, scoreDelta); 
        if (colMoved) {
            moved = true; 
        }
        for (int row = 0; row < grid.size(); ++row) {
            grid[grid.size() - 1 - row][col] = column[row]; //remets au bon endroit
        }
    }
    score += scoreDelta; // mise à jour du score 
    return moved;
}