#include "modele.hpp"   // Fonctions principales du jeu
#include "ai.hpp"       // Logique d'IA pour les décisions
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <curses.h>     // Pour l'affichage dans le terminal

// Fonction principale pour exécuter le jeu contrôlé par l'IA
int main() {
    int gridSize = 4;           // Taille de la grille (4x4 par défaut)
    int score = 0;              // Score actuel du jeu
    int bestScore = loadBestScore(); // Charger le meilleur score enregistré
    bool moved;                 // Indique si un mouvement a été effectué

    // Initialisation de la grille du jeu
    std::vector<std::vector<int>> grid(gridSize, std::vector<int>(gridSize, 0));
    std::srand(std::time(0));   // Graine pour les nombres aléatoires
    initscr();                  // Démarrer le mode ncurses
    noecho();                   // Désactiver l'affichage des entrées utilisateur
    cbreak();                   // Désactiver le buffering par ligne
    keypad(stdscr, TRUE);       // Activer les entrées clavier spéciales
    initializeColors();         // Initialiser les couleurs pour l'affichage

    initializeGrid(grid);       // Ajouter deux tuiles initiales dans la grille

    // Boucle principale du jeu
    while (true) {
        clear();                        // Effacer l'écran
        displayGrid(grid, score, bestScore); // Afficher la grille actuelle

        // Vérifier si le jeu est terminé
        if (isGameOver(grid)) {
            mvprintw(gridSize * 2 + 5, 0, "Game Over! Final Score: %d", score);
            mvprintw(gridSize * 2 + 6, 0, "Press any key to exit...");
            refresh();
            getch(); // Attendre une entrée de l'utilisateur avant de quitter
            break;
        }

        // Afficher le meilleur mouvement calculé par l'IA
        std::string bestMove = getBestMove(grid, score);
        mvprintw(gridSize * 2 + 7, 0, "AI's Best Move: %s", bestMove.c_str());
        mvprintw(gridSize * 2 + 8, 0, "Press Q to quit...");
        refresh();

        // Gestion des entrées utilisateur pour quitter ou continuer
        int ch = getch();
        if (ch == 'Q' || ch == 'q') {
            mvprintw(gridSize * 2 + 9, 0, "Quitting game...");
            refresh();
            break;
        }

        // Appliquer le meilleur mouvement choisi par l'IA
        moved = false;
        if (bestMove == "Up") moveUp(grid, moved, score);
        else if (bestMove == "Down") moveDown(grid, moved, score);
        else if (bestMove == "Left") moveLeft(grid, moved, score);
        else if (bestMove == "Right") moveRight(grid, moved, score);

        // Ajouter une tuile aléatoire si un mouvement valide a été effectué
        if (moved) {
            addRandomTile(grid);
        }

        // Petite pause pour un effet d'animation
        napms(300); // Pause de 300ms
    }

    // Afficher la grille et le score final après la fin du jeu ou après avoir quitté
    clear();
    displayGrid(grid, score, bestScore);
    mvprintw(gridSize * 2 + 5, 0, "Final Score: %d", score);
    mvprintw(gridSize * 2 + 6, 0, "Game exited. Thanks for playing!");
    refresh();
    getch(); // Attendre une entrée de l'utilisateur avant de quitter

    endwin(); // Quitter le mode ncurses
    return 0;
}
