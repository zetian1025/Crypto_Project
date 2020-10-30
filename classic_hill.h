#ifndef CLASSIC_HILL_H
#define CLASSIC_HILL_H

#include "cryptobase.h"
#include <string>
#include <vector>

class Classic_Hill : public CryptoBase
{
private:
    int MatrixSize;
    std::vector<std::vector<int>> Matrix;

    std::vector<std::vector<int>> inverseMatrix();
    int calcuCofactor(int i, int j);
    int modInverse(int a, int m);
    int isInvertible(std::vector<std::vector<int>> matrix, int n);

    QString Hill_Encryption(std::string plainText);
    QString Hill_Decryption(std::string cipherText);

public:
    static const int is_key_needed = true;

    Classic_Hill(int MatrixSize);
    Classic_Hill(QString Matrix);

    bool EncryptionText() override;
    bool DecryptionText() override;
};

#endif // CLASSIC_HILL_H
