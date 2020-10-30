#include "cryptobase.h"

CryptoBase::CryptoBase()
{
    CipherText = "";
    PlainText = "";
}

CryptoBase::CryptoBase(QString text, int mode) {
    if (mode == 0) PlainText = text;
    else CipherText = text;
}

QString CryptoBase::getPlainText(){
    return this->PlainText;
}

QString CryptoBase::getCipterText(){
    return this->CipherText;
}

void CryptoBase::setPlainText(QString text) {
    this->PlainText = text;
}

void CryptoBase::setCipterText(QString text){
    this->CipherText = text;
}



