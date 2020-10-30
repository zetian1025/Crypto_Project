#ifndef MODERN_RSA_H
#define MODERN_RSA_H

#include "biginteger.h"
#include "cryptobase.h"
#include <omp.h>

class Modern_RSA : public CryptoBase
{
private:
    BigInteger p, q, n;
    BigInteger Public_Key;
    BigInteger Private_Key;
    BigInteger eul_func;

    void init(const unsigned);

    BigInteger RSA_Encryption(const BigInteger &);
    BigInteger RSA_Decryption(const BigInteger &);

    BigInteger createOddNum(unsigned);
    BigInteger createPrime(unsigned, int);
    bool isPrime(const BigInteger &, const unsigned);
    BigInteger createRandomSmallNumber(const BigInteger &);
    void createExponent(const BigInteger &);

    bool valid(const QString &);
public:
    Modern_RSA();   //用于加密解密
    Modern_RSA(const unsigned len) { init(len); }    //用于生成密钥对

    QString getPublicKey();
    QString getBigN();
    QString getPrivateKey();

    bool setPublicKey(const QString &);
    bool setPrivateKey(const QString &);
    bool setN(const QString &);

    bool DecryptionText() override;
    bool EncryptionText() override;
};

#endif // MODERN_RSA_H
