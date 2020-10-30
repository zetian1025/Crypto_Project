#include "classic_caesar.h"

Classic_Caesar::Classic_Caesar(){

}

void Classic_Caesar::setKey(QString Key) {
    this->key = Key.toInt();
}

QString Classic_Caesar::CaesarChar_Encryption(QString s, int key)
{
    QString newS;
    for(QChar qch : s)
    {
        char ch = qch.toLatin1();
        if(ch>=65 && ch<=90)
        {
            ch = 'A' + (ch - 'A' + key)%26;
        }
        else if(ch>=97 && ch<=122)
        {
            ch = 'a' + (ch - 'a' + key)%26;
        }
        else if(ch>=48 && ch<=57)
        {
            ch = 48 + (ch - 48 + key)%10;
        }
        newS += QChar(ch);
    }
    return newS;
}

QString Classic_Caesar::CaesarChar_Decryption(QString s, int key)
{
    QString newS;
    for(QChar qch : s)
    {
        char ch = qch.toLatin1();
        if(ch>=65 && ch<=90)
        {
            ch = 'A'+(ch-'A'-key+26)%26;
        }
        else if(ch>=97 && ch<=122)
        {
            ch = 'a' + (ch - 'a' - key + 26)%26;
        }
        else if(ch>=48 && ch<=57)
        {
            ch = 48 + (ch - 48 - key + 10)%10;
        }
        newS += QChar(ch);
    }
    return newS;
}

bool Classic_Caesar::EncryptionText() {
    this->CipherText = CaesarChar_Encryption(PlainText, this->key);
    return true;
}

bool Classic_Caesar::DecryptionText(){
    this->PlainText = CaesarChar_Decryption(CipherText, key);
    return true;
}
