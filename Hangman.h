#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>
#include <set>

class HangmanGame {
private:
    std::string m_secretWord;
    std::set<char> m_guessedLetters;
    int m_maxAttempts;
    int m_wrongAttempts;

    void drawGallows() const;

public:
    explicit HangmanGame(const std::vector<std::string>& wordList, int maxAttempts = 6);

    void play();
    bool isWon() const;
    bool isLost() const;

    std::string getSecretWord() const;
    std::vector<char> getPlayerLetters() const;
    int getAttemptsUsed() const;
};

#endif