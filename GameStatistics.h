#ifndef GAME_STATISTICS_H
#define GAME_STATISTICS_H

#include <string>
#include <vector>

class GameStatistics {
private:
    std::string m_secretWord;
    std::vector<char> m_playerLetters;
    int m_attemptsUsed;
    double m_elapsedSeconds;

public:
    GameStatistics(const std::string& secretWord,
        const std::vector<char>& playerLetters,
        int attemptsUsed,
        double elapsedSeconds);

    void display() const;
    void saveToFile(const std::string& filename = "game_stats.txt") const;
};

#endif