#include "classic_morse.h"

Classic_Morse::Classic_Morse()
{

}

const std::vector<std::string> Classic_Morse::Morse_map = {"10","0111","0101","011","1","1101","001","1111","11","1000","010","1011","00","01","000","1001","0010","101","111","0","110","1110","100","0110","0100","0011","00000","10000","11000","11100","11110","11111","01111","00111","00011","00001"};

std::vector<QString> Classic_Morse::Morse_Encryption(QString s){
    std::string str = "";
    std::vector<QString> ans;
    for (QChar qch : s) {
        str += qch.toLatin1();
    }

    std::vector<std::string> stv = transNum(str);
    for (std::string _stv : stv) {
        std::string temp = "";
        for (char c : _stv) {
            if (c == '1') temp += '.';
            else if (c == '0') temp += '_';
            else temp += c;
        }
        ans.push_back(QString::fromStdString(temp));
    }

    return ans;
}

QString Classic_Morse::Morse_Decryption(QString qstr) {
    std::vector<QString> vofs;
    std::string temp = "", str = qstr.toUtf8().constData(), ans = "";
    for (char c : str) {
        if (c == '.') temp.push_back('1');
        else if (c == '_') temp.push_back('0');
        else if (c == ' ' || c == '\\') {
            vofs.push_back(QString::fromStdString(temp));
            temp = "";
        }
        else {
            vofs.push_back(QString::fromStdString(""+c));
            temp = "";
        }
    }

    if (temp != "") vofs.push_back(QString::fromStdString(temp));

    for (QString & qstr : vofs) {
        bool flag = false;
        std::string str = qstr.toUtf8().constData();
        for (int i=0; i<36; i++) {
            if (str == Morse_map[i]) {
                flag = true;
                if (i < 26) ans.push_back(char(i + 65));
                else ans.push_back(char(i + 22));
                break;
            }
        }

        if (!flag) ans += str;
    }

    return QString::fromStdString(ans);
}

std::vector<std::string> Classic_Morse::transNum(std::string s){
    std::vector<std::string> v;
    for(char c : s){
        c = toupper(c);
        if(c>=65 && c<=90) v.push_back(Morse_map[c-65]);
        else if(c>=48 && c<=57) v.push_back(Morse_map[c-48+26]);
        else v.push_back("" + c);
    }
    return v;
}

bool Classic_Morse::EncryptionText() {
    for (QChar qc : PlainText) {
        if (!qc.isLetterOrNumber()) return false;
    }

    std::vector<QString> ans = Morse_Encryption(PlainText);
    for (QString qstr : ans) {
        this->CipherText += qstr;
    }
    return true;
}

bool Classic_Morse::DecryptionText() {
    for (QChar qc : CipherText) {
        char c = qc.toLatin1();
        if (c == '.' || c == '_' || c == '\\') continue;
        else return false;
    }

    this->PlainText = Morse_Decryption(CipherText);
    return true;
}
