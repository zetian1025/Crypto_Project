#ifndef CRYPTOBASE_H
#define CRYPTOBASE_H

#include <QString>

//加密解密算法基本类，父类。包括最最基本的加密解密信息。

class CryptoBase
{
protected:
    enum mode{Encryption, Decryption};  //模式设置，加密或者解密
    QString CipherText;  //密文
    QString PlainText;  //明文
public:
    CryptoBase();
    CryptoBase(QString text, int mode);
    virtual bool EncryptionText()=0;
    virtual bool DecryptionText()=0;
    QString getCipterText();
    QString getPlainText();
    void setCipterText(QString text);
    void setPlainText(QString text);
};

#endif // CRYPTOBASE_H
