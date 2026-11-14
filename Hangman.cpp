#include "Hangman.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <cctype>

HangmanGame::HangmanGame(const std::vector<std::string>& wordList, int maxAttempts)
    : m_maxAttempts(maxAttempts), m_wrongAttempts(0) {
    if (wordList.empty()) {
        m_secretWord = "TEST";
    }
    else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, wordList.size() - 1);
        m_secretWord = wordList[dis(gen)];
    }
}

void HangmanGame::drawGallows() const {
    std::cout << "\n  +---+     \n";
    std::cout << "  |   |     \n";
    std::cout << "  " << (m_wrongAttempts > 0 ? "O" : " ") << "   |     \n";
    std::cout << " " << (m_wrongAttempts > 2 ? "/" : " ")
        << (m_wrongAttempts > 1 ? "|" : " ")
        << (m_wrongAttempts > 3 ? "\\" : " ") << "  |     \n";
    std::cout << " " << (m_wrongAttempts > 4 ? "/" : " ")
        << " " << (m_wrongAttempts > 5 ? "\\" : " ") << "  |     \n";
    std::cout << "      |     \n";
    std::cout << "=========\n";
}

void HangmanGame::play() {
    char inputChar;
    while (!isWon() && !isLost()) {
        drawGallows();

        std::cout << "\nWord: ";
        bool wordComplete = true;
        for (char c : m_secretWord) {
            if (m_guessedLetters.count(c)) {
                std::cout << c << " ";
            }
            else {
                std::cout << "_ ";
                wordComplete = false;
            }
        }
        std::cout << "\n";

        if (wordComplete) break;

        std::cout << "Used letters: ";
        for (char c : m_guessedLetters) {
            std::cout << c << " ";
        }
        std::cout << "\n";

        std::cout << "Attempts remaining: " << (m_maxAttempts - m_wrongAttempts) << "\n";
        std::cout << "Enter a letter: ";

        if (!(std::cin >> inputChar)) break;

        inputChar = std::toupper(inputChar);

        if (m_guessedLetters.count(inputChar)) {
            std::cout << "You have already entered this letter!\n";
            continue;
        }

        m_guessedLetters.insert(inputChar);

        if (m_secretWord.find(inputChar) == std::string::npos) {
            m_wrongAttempts++;
            std::cout << "There is no such letter in the word!\n";
        }
        else {
            std::cout << "Correct! The letter is in the word.\n";
        }
    }
}

bool HangmanGame::isWon() const {
    for (char c : m_secretWord) {
        if (m_guessedLetters.find(c) == m_guessedLetters.end()) {
            return false;
        }
    }
    return true;
}

bool HangmanGame::isLost() const {
    return m_wrongAttempts >= m_maxAttempts;
}

std::string HangmanGame::getSecretWord() const {
    return m_secretWord;
}

std::vector<char> HangmanGame::getPlayerLetters() const {
    std::vector<char> letters(m_guessedLetters.begin(), m_guessedLetters.end());
    return letters;
}

int HangmanGame::getAttemptsUsed() const {
    return m_wrongAttempts;
}