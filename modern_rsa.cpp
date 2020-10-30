#include "modern_rsa.h"
#include <string>
#include <sstream>
#include <QDebug>
#include <ctime>

using std::string;

Modern_RSA::Modern_RSA(){

}

void Modern_RSA::init(const unsigned len) {
    assert(len > 0);
    srand(time(0));

    BigInteger numbers[3];

    #pragma omp parallel for num_threads(2)
    for (int i=0; i<2; i++) {
        BigInteger num = createPrime(len, 20);
        numbers[i] = num;
    }

    this->p = numbers[0];
    this->q = numbers[1];

    this->n = p*q;
    this->eul_func = (p-1)*(q-1);
    createExponent(eul_func);
}

bool Modern_RSA::isPrime(const BigInteger & bigInteger, const unsigned int k) {
    assert(k > 0);
    if (bigInteger == BigInteger::ZERO) return false;
    else if (bigInteger == BigInteger::ONE) return false;
    else if (bigInteger == BigInteger::TWO) return true;

    BigInteger d = bigInteger - 1;
    BigInteger::bit b(d);    //转换为二进制
    size_t s = 0;
    for (size_t i=0; i<b.size(); i++) {
        if (b.at(i) == 0) {
            s++;
            d = d.shiftRight(1);
        }
        else break;
    }

    clock_t start = clock();

    for (size_t i=1; i<=k; i++) {
        BigInteger a = createRandomSmallNumber(bigInteger);
        BigInteger x = a.modAndpow(d, bigInteger);
        if (x == BigInteger::ONE) continue;

        bool flag = true;
        for (size_t r=0; r<s; r++) {
            if (!flag) break;
            if (x == bigInteger-1) flag = false;
//            x = (x*x) % bigInteger;
            x = x.multiply(x).mod(bigInteger);
        }
        if (flag) {
            clock_t end = clock();
            qDebug() << "end-start:" << (double)(end-start)/CLOCKS_PER_SEC;

            return false;
        }
    }
    clock_t end = clock();
    qDebug() << "end-start:" << (double)(end-start)/CLOCKS_PER_SEC;

    return true;
}

BigInteger Modern_RSA::createRandomSmallNumber(const BigInteger & val) {
    BigInteger::base_t t = 0;
    do {
        t = rand();
    } while (t == 0);

    BigInteger Rand_val(t);
    BigInteger ans = Rand_val%val;
    if (ans == BigInteger::ZERO) ans = val - BigInteger::ONE;
    return ans;
}

BigInteger Modern_RSA::createPrime(unsigned int len, int k) {
    assert(k > 0);
    BigInteger Temp_Prime = createOddNum(len);
    int flag = 1;

    while (!isPrime(Temp_Prime, k)) {
        Temp_Prime = createOddNum(len);
        qDebug() << "CreatePrime" << flag++ << "in" << omp_get_thread_num();
    }

    return Temp_Prime;
}

BigInteger Modern_RSA::createOddNum(unsigned int len) {
    static const char table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    len >>= 2;  //将二进制长度转换为16进制长度(除4)
    if (len) {

        /*  原方法，利用了ostringstream
        std::ostringstream oss;
        for (size_t i=0; i < len-1; i++)
            oss << table[rand()%16];
        oss << table[1];
        return BigInteger(oss.str());
        */

        string bigNumber = "";
        while (len > 1) {
            bigNumber += table[(rand()*rand())%16];
            len--;
        }
        bigNumber += '1';
        return BigInteger(bigNumber);
    }
    return BigInteger('F');
}

void Modern_RSA::createExponent(const BigInteger & eul_func) {
    this->Public_Key = 65537;
    this->Private_Key = this->Public_Key.modAndinverse(eul_func);
}

BigInteger Modern_RSA::RSA_Encryption(const BigInteger & plainText) {
    BigInteger EncryptionText = plainText.modAndpow(this->Public_Key, this->n);
    return EncryptionText;
}

BigInteger Modern_RSA::RSA_Decryption(const BigInteger & cipherText) {
    BigInteger DecryptionText = cipherText.modAndpow(this->Private_Key, this->n);
    return DecryptionText;
}

bool Modern_RSA::setPrivateKey(const QString & InputText) {
    if (!valid(InputText)) return false;
    string inputText = InputText.toStdString();
    this->Private_Key = BigInteger(inputText);
    return true;
}

bool Modern_RSA::setPublicKey(const QString & InputText) {
    if (!valid(InputText)) return false;
    string inputText = InputText.toStdString();
    this->Public_Key = BigInteger(inputText);
    return true;
}

bool Modern_RSA::setN(const QString & InputText) {
    if (!valid(InputText)) return false;
    string inputText = InputText.toStdString();
    this->n = BigInteger(inputText);
    return true;
}

QString Modern_RSA::getBigN() {
    string N = this->n.toString();
    return QString::fromStdString(N);
}

QString Modern_RSA::getPublicKey() {
    string public_key = this->Public_Key.toString();
    return QString::fromStdString(public_key);
}

QString Modern_RSA::getPrivateKey(){
    string private_key = this->Private_Key.toString();
    return QString::fromStdString(private_key);
}

bool Modern_RSA::valid(const QString & InputText) {
    string inputText = InputText.toStdString();
    for (std::string::const_iterator it=inputText.begin(); it!=inputText.end(); ++it) {
        if (!isalnum(*it))    // 不是字母或者数字
            return false;
        if (isalpha(*it)) {
            char ch = tolower(*it);
            if (ch > 'f')    // 超过十六进制字符'f'
                return false;
        }
    }
    return true;
}

bool Modern_RSA::DecryptionText(){
    if (!valid(this->CipherText)) return false;
    BigInteger ans = RSA_Decryption(BigInteger(this->CipherText.toStdString()));
    this->PlainText = QString::fromStdString(ans.toString());
    return true;
}

bool Modern_RSA::EncryptionText(){
    if (!valid(this->PlainText)) return false;
    BigInteger ans = RSA_Encryption(BigInteger(this->PlainText.toStdString()));
    this->CipherText = QString::fromStdString(ans.toString());
    return true;
}

