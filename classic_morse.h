#ifndef CLASSIC_MORSE_H
#define CLASSIC_MORSE_H

#include "cryptobase.h"
#include <string>
#include <vector>

class Classic_Morse : public CryptoBase
{
private:
    std::vector<QString> Morse_Encryption(QString s);
    QString Morse_Decryption(QString s);
    std::vector<std::string> transNum(std::string s);
public:
    static const std::vector<std::string> Morse_map;
    static const int is_key_needed = false;
    Classic_Morse();
    bool EncryptionText() override;
    bool DecryptionText() override;
};

#endif // CLASSIC_MORSE_H
