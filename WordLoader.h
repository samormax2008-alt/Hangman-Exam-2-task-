#ifndef WORD_LOADER_H
#define WORD_LOADER_H

#include <string>
#include <vector>

class WordLoader {
private:
    std::string m_filename;
    char m_encryptionKey;

    std::string decryptString(const std::string& cipherText) const;

public:
    explicit WordLoader(const std::string& filename, char key = 'K');
    std::vector<std::string> loadWords() const;
    void createSampleEncryptedFile() const;
};

#endif