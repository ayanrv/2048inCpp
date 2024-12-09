#include "modele.hpp"
#include "menu.hpp"  // Include the menu header
#include "ai.hpp"
#include <chrono>    // For timed mode support
#include <curses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

// Fonction principale pour exécuter le jeu 2048.
// Initialise les paramètres de la grille, les modes de jeu, le score et les entrées utilisateur.
int main() {
    int gridSize = 4;     // plateau par default
    int score = 0; // Initialise le score du jeu
    int bestScore = loadBestScore(); // charge le meilleur score du fichier
    int input; // utilise int au lieu de char pour l'input du joueur
    bool undoAvailable = false; // regarde si undo est possible
    int prevScore = 0;      // Stock le score precedent 
    std::string currentHint = "";

    // avant d'initialiser le plateau
    bool timedMode = false;
    int timeLimit = 120;  //limite de temps par default

     //appele le menu pour définir la taille de la grille, le mode chronométré et la limite de temps
    showMenu(timedMode, timeLimit, gridSize);

    // Initialise la grille de manière dynamique en fonction de gridSize
    std::vector<std::vector<int>> grid(gridSize, std::vector<int>(gridSize, 0)); // plateau actuel 
    std::vector<std::vector<int>> prevGrid(gridSize, std::vector<int>(gridSize, 0)); // plateau precedent

    std::srand(std::time(0)); // Générateur de nombres aléatoires pour le placement aléatoire de tuiles
    
    // initialise l'ecran ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); // Active la saisie à l'aide des touches fléchées

    initializeColors(); // initialise les paires de couleur pour le jeu 
    initializeGrid(grid); // rajoute deux tuiles aleatoire pour commencer le jeu

    auto startTime = std::chrono::steady_clock::now();

    // Boucle de jeu principale
    while (true) {
        clear(); // efface l'ecran pour preparer le prochain affichage du plateau 
        displayGrid(grid, score, bestScore); //affiche l'ecran, le score, et le meilleur score  

        // Vérifiez le chronometre uniquement si le mode chronométré est activé
        if (timedMode) {
            auto now = std::chrono::steady_clock::now();
            int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

             mvprintw(gridSize * 2 + 6, 0, "Time left: %d seconds", timeLimit - elapsed);

            if (elapsed >= timeLimit) {
                mvprintw(gridSize * 2 + 6, 0, "Time's up! Game over.");
                refresh();
                getch();
                break;
            }
        }

        // regarde si le jeu est fini
        if (isGameOver(grid)) {
            mvprintw(gridSize * 2 + 5, 0, "Game Over! No more valid moves!"); // affiche game over
            mvprintw(gridSize * 2 + 6, 0, "Press any key to exit...");
            refresh(); // Actualisez l'écran pour afficher le message de game over
            getch(); // Attendez que l'utilisateur saisisse la touche pour confirmer la fin du jeu
            break; // Quitte la boucle de jeu principale
        }

        // montre indice si possible 
        if (!currentHint.empty()) {
            mvprintw(gridSize * 2 + 9, 0, "Hint: %s", currentHint.c_str());
        }

        // montre les instructions pour les input du joueur
        mvprintw(gridSize * 2 + 2, 0, "Press U to Undo, H for Hint, Arrow Keys/WASD to move, Q to Quit.");
        refresh();
        input = getch(); // prend le input du sujet

        bool validMove = false; //Drapeau pour vérifier si l'entrée est valide
        bool moved = false; // drapeau pour voir si le plateau a changé 

        // sauvegarde l'etat actuel avant de faire des changement/mouvement
        if (input == 'W' || input == 'w' || input == KEY_UP ||
            input == 'A' || input == 'a' || input == KEY_LEFT ||
            input == 'S' || input == 's' || input == KEY_DOWN ||
            input == 'D' || input == 'd' || input == KEY_RIGHT) {
            prevGrid = grid; // Sauvegarde le plateau
            prevScore = score; // Sauvegarde le score
            undoAvailable = true; // Undo devient possible apres la sauvegarde
        }

        // gere les entrees des utilisateurs et effectue les mouvements
        switch (input) {
            case 'W': case 'w': case KEY_UP:
                validMove = moveUp(grid, moved, score); break; // Move up
            case 'A': case 'a': case KEY_LEFT:
                validMove = moveLeft(grid, moved, score); break; // Move left
            case 'S': case 's': case KEY_DOWN:
                validMove = moveDown(grid, moved, score); break; // Move down
            case 'D': case 'd': case KEY_RIGHT:
                validMove = moveRight(grid, moved, score); break; // Move right
            case 'U': case 'u': // Undo
                if (undoAvailable) {
                    grid = prevGrid; // remets le plateau a son etat precedent 
                    score = prevScore; // remets le score a son etat precedent 
                    undoAvailable = false; // Undo est possible
                } 
                refresh();
                continue; // ignore le reste de la boucle apres undo 
            case 'H': case 'h': // pour l'indice 
                currentHint = getBestMove(grid, score);
                if (currentHint == "None") {
                    currentHint = "No valid move found.";
                }
                continue; // Passe le reste de la boucle après avoir montré l'indice
            case 'Q': case 'q':
                endwin(); // arrete le mode ncurses
                return 0;
            default:
                mvprintw(gridSize * 2 + 7, 0, "Invalid input. Use Arrow Keys or WASD.");
                refresh();
                continue; // ignore le reste et attends un autre input 
        }

        // si le mouvement etait possible et que le plateau a changé, rajoute une tuile aleatoire
        if (validMove && moved) {
            addRandomTile(grid); // ajoute une nouvelle tuile aleatoire apres avoir sauvegarder l'etat actuel
            currentHint = "";  // efface l'indice apres un mouvement validé
        }
    }

     // mis à jour du bestscore si le score est plus grand 
    if (score > bestScore) {
        bestScore = score;
        saveBestScore(bestScore); //ajoute le nouveau meilleur score au fichier
    }

    endwin(); // arrete le mode ncurses et reinstaure le terminal
    return 0;
}