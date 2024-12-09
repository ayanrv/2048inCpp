#include "menu.hpp"
#include <iostream>
#include <algorithm>
#include <fstream> 

// fonction pour enregistrer le meilleur score dans un fichier specifique
void saveBestScore(int bestScore) {
    std::ofstream file("data/best_score.txt"); // Le chemin du fichier inclut le dossier "data"
    if (file.is_open()) {
        file << bestScore;
        file.close();
    }
}

//Fonction pour charger le meilleur score à partir d’un fichier situé dans un dossier spécifique
int loadBestScore() {
    std::ifstream file("data/best_score.txt"); // Le chemin du fichier inclut le dossier "data"
    int bestScore = 0;
    if (file.is_open()) {
        file >> bestScore;
        file.close();
    }
    return bestScore;
}

//Fonction pour afficher le menu principal et permettre à l'utilisateur de choisir les paramètres du jeu
void showMenu(bool &timedMode, int &timeLimit, int &gridSize) {
    while (true) {
        std::cout << "\n--- 2048 Game Menu ---\n";
        std::cout << "1. Start Game (Current Grid Size: " << gridSize << "x" << gridSize << ")\n";
        std::cout << "2. Select Game Mode\n";
        std::cout << "3. Change Grid Size\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                return;  // commence le jeu
            case 2:
                std::cout << "1. Classic Mode\n";
                std::cout << "2. Timed Mode\n";
                std::cout << "Select mode: ";
                int mode;
                std::cin >> mode;

                if (mode == 2) {
                    timedMode = true;
                    std::cout << "Enter time limit (in seconds): ";
                    std::cin >> timeLimit;
                    timeLimit = std::max(timeLimit, 10);  // temps minimun autorisé
                } else {
                    timedMode = false;
                }
                break;
            case 3:
                std::cout << "Enter new grid size (4, 5, or 6): ";
                std::cin >> gridSize;
                if (gridSize < 4 || gridSize > 6) {
                    std::cout << "Invalid grid size! Defaulting to 4x4.\n";
                    gridSize = 4;
                }
                break;
            case 4:
                exit(0);  // arreter/quitter le jeu
            default:
                std::cout << "Invalid input! Please try again.\n";
        }
    }
}