#include "docompute.h"
#include "CodeException.h"
#include "classic_caesar.h"
#include "classic_morse.h"
#include "classic_hill.h"
#include "modern_rsa.h"
#include <QDebug>


DoCompute::DoCompute()
{
    codeIndex = -1;
    RSAIndex = 0;
    mode = -1;
    InputText = InputText_key = OutputText = nullptr;
}

void DoCompute::setcodeIndex(int index){
    this->codeIndex = index;
}
void DoCompute::setRSAIndex(int index){
    this->RSAIndex = index;
}
void DoCompute::setMode(int mode){
    this->mode = mode;
}
void DoCompute::setInputText(QString text) {
   this->InputText = text;
}
void DoCompute::setInputText_key(QString text){
    this->InputText_key = text;
}
void DoCompute::setOutputText(QString text){
    this->OutputText = text;
}
int DoCompute::getcodeIndex(){
    return this->codeIndex;
}
int DoCompute::getRSAIndex(){
    return this->RSAIndex;
}
int DoCompute::getMode(){
    return this->mode;
}
QString DoCompute::getInputText(){
    return this->InputText;
}
QString DoCompute::getInputText_key(){
    return this->InputText_key;
}
QString DoCompute::getOutputText(){
    return this->OutputText;
}
QString DoCompute::getRSA_Public(){
    return this->RSA_Public;
}
QString DoCompute::getRSA_Private(){
    return this->RSA_Private;
}
QString DoCompute::getRSA_bigN(){
    return this->RSA_bigN;
}


inline int DoCompute::vaild(){
    if (codeIndex==-1) return CODEINDEX_MISSING;
    if (mode == -1) return MODE_MISSING;
    if (InputText==nullptr) return INPUT_TEXT_MISSING;

    return OK;
}

int DoCompute::DoComputeNow(bool is_key_added) {
    int isVaild = vaild();
    if (isVaild != OK) {
        return isVaild;
    }

    switch (codeIndex) {
    case 1: {
        Classic_Caesar obj_1;
        if (obj_1.is_key_needed && !is_key_added) return INPUT_TEXT_KEY_MISSING;
        if (mode == 0) {
            obj_1.setPlainText(InputText);
            obj_1.setKey(InputText_key);
            if (obj_1.EncryptionText()) setOutputText(obj_1.getCipterText());
        }
        else {
            obj_1.setCipterText(InputText);
            obj_1.setKey(InputText_key);
            if (obj_1.DecryptionText()) setOutputText(obj_1.getPlainText());
        }
        break;
    }

    case 2: {
        Classic_Morse obj_2;
        if (obj_2.is_key_needed && !is_key_added) return INPUT_TEXT_KEY_MISSING;
        if (mode == 0) {
            obj_2.setPlainText(InputText);
            if (obj_2.EncryptionText()) setOutputText((obj_2.getCipterText()));
            else return INPUT_FORMAT_ERROR;
        }
        else {
            obj_2.setCipterText(InputText);
            if (obj_2.DecryptionText()) setOutputText(obj_2.getPlainText());
            else return INPUT_FORMAT_ERROR;
        }
        break;
    }
    case 3:{
        if (!is_key_added) return INPUT_TEXT_KEY_MISSING;
        Classic_Hill obj_3(InputText_key);
        if (mode == 0) {
            obj_3.setPlainText(InputText);
            if (obj_3.EncryptionText()) setOutputText(obj_3.getCipterText());
            else return INPUT_KEY_VALUE_ERROR;
        }
        else {
            obj_3.setCipterText(InputText);
            if (obj_3.DecryptionText()) setOutputText(obj_3.getPlainText());
            else return INPUT_KEY_VALUE_ERROR;
        }
        break;
    }

    case 4:{
        if (!is_key_added) return INPUT_TEXT_KEY_MISSING;
        Modern_RSA obj_4;
        QString InputKey = InputText_key;
        if (InputText_key.count(',') != 1) return INPUT_KEY_VALUE_ERROR;
        if (InputKey.front() != '[' || InputKey.back() != ']') return INPUT_FORMAT_ERROR;
        InputKey = InputKey.mid(1, InputKey.size()-2);
        if (!obj_4.setN(InputKey.section(',', 0, 0))) return INPUT_KEY_VALUE_ERROR;
        if (mode == 0) {
            if (!obj_4.setPublicKey(InputKey.section(',', 1, 1))) return INPUT_KEY_VALUE_ERROR;
            obj_4.setPlainText(InputText);
            if (obj_4.EncryptionText()) setOutputText(obj_4.getCipterText());
            else return INPUT_FORMAT_ERROR;
        }
        else {
            if (!obj_4.setPrivateKey(InputKey.section(',', 1, 1))) return INPUT_KEY_VALUE_ERROR;
            obj_4.setCipterText(InputText);
            if (obj_4.DecryptionText()) setOutputText(obj_4.getPlainText());
            else return INPUT_FORMAT_ERROR;
        }
    }
    }

    return OK;
}

void DoCompute::doRSAinit(){
    static const unsigned int table[] = {256, 512, 1024, 2048, 4196};
    Modern_RSA obj;
    if (RSAIndex >= 0) obj = Modern_RSA(table[RSAIndex]);
    else obj = Modern_RSA(table[0]);

    this->RSA_Public = "====PUBLIC KEY BEGIN====\n\n" + obj.getPublicKey() + "\n\n====PUBLIC KEY END====";
    this->RSA_Private = "====PRIVATE KEY BEGIN====\n\n" + obj.getPrivateKey() + "\n\n====PUBLIC KEY END====";
    this->RSA_bigN = "====N BEGIN====\n\n" + obj.getBigN() + "\n\n====N KEY END====";
}

