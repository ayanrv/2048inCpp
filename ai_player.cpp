#include "modele.hpp"   // Fonctions de logique du jeu
#include "ai.hpp"       // Prise de décision de l'IA
#include <vector>       // Représentation dynamique de la grille 2D
#include <iostream>     // Pour le débogage et l'affichage (si nécessaire)
#include <cstdlib>      // Pour la génération de nombres aléatoires
#include <ctime>        // Pour initialiser le générateur aléatoire
#include <curses.h>     // Pour l'affichage graphique avec ncurses

// Fonction principale pour exécuter le jeu piloté par l'IA
int main() {
    int gridSize = 4;         // Définir la taille de la grille de jeu
    int score = 0;            // Initialiser le score actuel du jeu
    int bestScore = loadBestScore(); // Charger le meilleur score à partir d'un fichier sauvegardé
    bool moved;               // Suivre si un mouvement a été effectué

    // Initialiser la grille du jeu comme un vecteur 2D rempli de zéros
    std::vector<std::vector<int>> grid(gridSize, std::vector<int>(gridSize, 0));

    // Initialiser le générateur de nombres aléatoires basé sur l'heure actuelle
    std::srand(std::time(0));

    // Initialiser l'écran ncurses pour l'affichage graphique
    initscr();              // Démarrer le mode ncurses
    noecho();               // Désactiver l'écho de la saisie
    cbreak();               // Désactiver la mise en tampon des lignes
    keypad(stdscr, TRUE);   // Activer les touches spéciales et flèches
    initializeColors();     // Initialiser les couleurs des tuiles du jeu

    // Ajouter deux tuiles aléatoires pour démarrer le jeu
    initializeGrid(grid);

    // Boucle principale du jeu IA
    while (true) {
        clear();                        // Effacer l'écran pour le prochain affichage
        displayGrid(grid, score, bestScore);  // Afficher l'état actuel du jeu

        // Afficher les informations et instructions du jeu
        mvprintw(gridSize * 2 + 3, 0, "Press Q to quit");
        mvprintw(gridSize * 2 + 4, 0, "Score: %d", score);
        mvprintw(gridSize * 2 + 5, 0, "Best Score: %d", bestScore);

        timeout(0);         // Vérification d'entrée non bloquante
        int ch = getch();   // Obtenir la saisie du joueur
        if (ch == 'q' || ch == 'Q') {  // Vérifier la commande de sortie
            break;          // Quitter la boucle de jeu
        }

        if (isGameOver(grid)) {  // Vérifier si le jeu est terminé
            mvprintw(gridSize * 2 + 6, 0, "Game Over! No more valid moves.");
            refresh();      // Mettre à jour l'affichage
            break;          // Quitter la boucle de jeu
        }

        // Obtenir le meilleur mouvement de l'algorithme de décision de l'IA
        std::string bestMove = getBestMove(grid, score);
        mvprintw(gridSize * 2 + 7, 0, "AI's Best Move: %s", bestMove.c_str());
        refresh();          // Mettre à jour l'écran avec la décision de l'IA

        // Effectuer le mouvement suggéré par l'IA
        if (bestMove == "Up") moveUp(grid, moved, score);
        else if (bestMove == "Down") moveDown(grid, moved, score);
        else if (bestMove == "Left") moveLeft(grid, moved, score);
        else if (bestMove == "Right") moveRight(grid, moved, score);
        else {  // Aucun mouvement valide restant
            mvprintw(gridSize * 2 + 8, 0, "No valid moves! Ending game.");
            refresh();      // Mettre à jour l'affichage
            break;          // Quitter la boucle de jeu
        }

        if (moved) addRandomTile(grid); // Ajouter une tuile aléatoire si le mouvement a réussi

        napms(300);          // Délai pour une animation plus fluide
    }

    // Affichage final du résumé
    clear();   // Effacer l'écran pour le résumé final
    mvprintw(0, 0, "==== Final Game State Summary ====");
    displayGrid(grid, score, bestScore);  // Afficher l'état final du jeu
    mvprintw(gridSize * 2 + 3, 0, "Final Score: %d", score);  // Afficher le score final
    mvprintw(gridSize * 2 + 4, 0, "Best Score Achieved: %d", bestScore);  // Afficher le meilleur score
    mvprintw(gridSize * 2 + 5, 0, "Press Q to exit...");  // Demande de quitter le jeu

    // Attendre la confirmation de l'utilisateur pour quitter le jeu
    while (true) {
        int ch = getch();  // Attendre la saisie d'une touche
        if (ch == 'q' || ch == 'Q') break;  // Quitter si 'Q' ou 'q' est pressé
    }

    endwin();  // Fermer l'écran ncurses et restaurer le terminal
    return 0;  // Terminer le programme
}
