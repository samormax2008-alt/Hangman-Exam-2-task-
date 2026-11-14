#include "WordLoader.h"
#include <fstream>
#include <iostream>

WordLoader::WordLoader(const std::string& filename, char key)
    : m_filename(filename), m_encryptionKey(key) {
}

std::string WordLoader::decryptString(const std::string& cipherText) const {
    std::string plainText = "";
    for (char c : cipherText) {
        plainText += (c ^ m_encryptionKey);
    }
    return plainText;
}

void WordLoader::createSampleEncryptedFile() const {
    std::ofstream outFile(m_filename);
    if (outFile.is_open()) {
        std::vector<std::string> sampleWords = {
            "PROGRAMMING", "NAVIGATION", "UKRAINE",
            "BUILDING", "CAT", "VEHICLE", "ALGORITHM"
        };
        for (const auto& word : sampleWords) {
            std::string encrypted = "";
            for (char c : word) {
                encrypted += (c ^ m_encryptionKey);
            }
            outFile << encrypted << "\n";
        }
    }
}

std::vector<std::string> WordLoader::loadWords() const {
    std::vector<std::string> words;
    std::ifstream inFile(m_filename);

    if (!inFile.is_open()) {
        createSampleEncryptedFile();
        inFile.open(m_filename);
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            if (line.back() == '\r') line.pop_back();
            std::string decrypted = decryptString(line);
            words.push_back(decrypted);
        }
    }
    return words;
}