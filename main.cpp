#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include "WordLoader.h"
#include "Hangman.h"
#include "GameStatistics.h"

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    std::cout << "========================================\n";
    std::cout << "       HANGMAN GAME          \n";
    std::cout << "========================================\n";

    WordLoader loader("words.enc");
    std::vector<std::string> words = loader.loadWords();

    if (words.empty()) {
        std::cerr << "Error: Failed to load the word list!\n";
        return 1;
    }

    char playAgain = 'y';
    do {
        auto startTime = std::chrono::high_resolution_clock::now();

        HangmanGame game(words);
        game.play();

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = endTime - startTime;

        if (game.isWon()) {
            std::cout << "\n[VICTORY!] You guessed the word: " << game.getSecretWord() << "\n";
        }
        else {
            std::cout << "\n[GAME OVER!] You lost. The secret word was: " << game.getSecretWord() << "\n";
        }

        GameStatistics stats(
            game.getSecretWord(),
            game.getPlayerLetters(),
            game.getAttemptsUsed(),
            elapsed.count()
        );

        stats.display();
        stats.saveToFile("game_stats.txt");

        std::cout << "\nDo you want to play again? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "Thanks for playing!\n";
    return 0;
}