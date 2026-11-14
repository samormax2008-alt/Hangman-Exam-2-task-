#include "GameStatistics.h"
#include <iostream>
#include <fstream>

GameStatistics::GameStatistics(const std::string& secretWord,
    const std::vector<char>& playerLetters,
    int attemptsUsed,
    double elapsedSeconds)
    : m_secretWord(secretWord), m_playerLetters(playerLetters),
    m_attemptsUsed(attemptsUsed), m_elapsedSeconds(elapsedSeconds) {
}

void GameStatistics::display() const {
    std::cout << "\n========================================\n";
    std::cout << "           GAME STATISTICS               \n";
    std::cout << "========================================\n";
    std::cout << "Search word: " << m_secretWord << "\n";
    std::cout << "Amount of time: " << m_elapsedSeconds << " seconds\n";
    std::cout << "Number of failed attempts: " << m_attemptsUsed << "\n";
    std::cout << "Letters Entered: ";
    for (char c : m_playerLetters) {
        std::cout << c << " ";
    }
    std::cout << "\n========================================\n";
}

void GameStatistics::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::app);
    if (outFile.is_open()) {
        outFile << "--- Game results ---\n";
        outFile << "Search word: " << m_secretWord << "\n";
        outFile << "Time: " << m_elapsedSeconds << " sec\n";
        outFile << "Failed attempts: " << m_attemptsUsed << "\n";
        outFile << "Entered letters: ";
        for (char c : m_playerLetters) {
            outFile << c << " ";
        }
        outFile << "\n---------------------\n\n";
        std::cout << "[The statistics have been successfully saved to a file '" << filename << "']\n";
    }
    else {
        std::cerr << "[Error saving statistics to a file!]\n";
    }
}