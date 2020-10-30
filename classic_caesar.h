#ifndef CLASSIC_CAESAR_H
#define CLASSIC_CAESAR_H
#include "cryptobase.h"

//古典加密算法-凯撒密码（序号index = 1）

class Classic_Caesar : public CryptoBase    //继承自父类（加密解密算法基本类）
{
private:
    int key;
    QString CaesarChar_Encryption(QString s, int key);
    QString CaesarChar_Decryption(QString s, int key);
public:
    static const int is_key_needed = true;
    Classic_Caesar();
    void setKey(QString key);
//    Classic_Caesar(QString text, int mode, int key=rand());
    bool EncryptionText() override;
    bool DecryptionText() override;
};

#endif // CLASSIC_CAESAR_H
