#include "classic_hill.h"
#include <string>
#include <QQueue>
#include <math.h>
#include <QDebug>

using std::vector;
using std::string;

Classic_Hill::Classic_Hill(int MatrixSize)
{

    this->MatrixSize = MatrixSize;
    this->Matrix = vector<vector<int>>(MatrixSize, vector<int>(MatrixSize));
    do{
        for (int i=0; i<MatrixSize; i++) {
            for (int j=0; j<MatrixSize; j++) {
                this->Matrix[i][j] = rand()%200;
            }
        }
    } while(!isInvertible(this->Matrix, this->MatrixSize));
}

Classic_Hill::Classic_Hill(QString MatrixString) {
    int size = MatrixString.count('[') - 1;
    this->MatrixSize = size;

    vector<vector<int>> Matrix(size, vector<int>(size, 0));
    QQueue<QString> StringQueue;
    QString tempString("");
    MatrixString = MatrixString.mid(1, MatrixString.size()-2);
    for (QChar qc : MatrixString) {
        if (qc.toLatin1() == '[') {
            StringQueue.push_back(tempString);
            tempString.clear();
        }
        else if (qc.toLatin1() == ']') continue;
        else {
            tempString += qc;
        }
    }
    StringQueue.push_back(tempString);
    StringQueue.pop_front();

    for (int i=0; i<size; i++) {
        QString subString = StringQueue.head();
        StringQueue.pop_front();
        for (int j=0; j<size; j++) {
            int num = subString.section(',', j, j).toInt();
            Matrix[i][j] = num;
        }
    }
    this->Matrix = Matrix;
}

QString Classic_Hill::Hill_Encryption(string plaintext) {
    string cipher = "";
    int k = 0;
    int size = plaintext.length();
    while(k < size){
        for(int i=0;i<MatrixSize;i++){
            int sum = 0;
            int temp = k;
            for(int j=0;j<MatrixSize;j++){
                sum += (Matrix[i][j]%26*(plaintext[temp++]-'A')%26)%26;
                sum = sum%26;
            }
            cipher += (sum+'A');
        }
        k += MatrixSize;
    }

    return QString::fromStdString(cipher);
}

QString Classic_Hill::Hill_Decryption(std::string cipherText){
    string cipher = "";
    int k = 0, size = cipherText.size();
    auto iMatrix = inverseMatrix();

    for(char &ch : cipherText) {
        ch = toupper(ch);
    }

    while(k < size){
        for(int i=0; i<MatrixSize; i++){
            int sum = 0;
            int temp = k;
            for(int j=0; j<MatrixSize; j++){
                sum += ((iMatrix[i][j]+26)%26*(cipherText[temp++]-'A')%26)%26;
                sum = sum%26;
            }
            cipher += (sum+'A');
        }
        k += MatrixSize;
    }

    return QString::fromStdString(cipher);
}

bool Classic_Hill::EncryptionText(){
    int index_1 = 0;
    int index_2 = 0;

    string newPlaintext;//保存处理过的明文，去除非字母，并在矩阵没有字符处添'x'
    string cipher;//加密后的结果
    string plaintext = this->PlainText.toUtf8().constData();

    if (isInvertible(Matrix, MatrixSize) == 0) return false;

    for(char ch : plaintext) {
        ch = toupper(ch);
        if(ch >= 65&&ch <= 90)
        {
            if(index_2 == MatrixSize)
            {
                index_1++;
                index_2 = 0;
            }
            newPlaintext += ch;//输入明文转化为对应的数字
            index_2++;
        }
    }

    for(int i = 0;i < MatrixSize-index_2;i++) newPlaintext+='x';

    this->CipherText = Hill_Encryption(newPlaintext);//Hill算法

    return true;
}

bool Classic_Hill::DecryptionText(){
    if (isInvertible(Matrix, MatrixSize) == 0) return false;
    string cipherText = this->CipherText.toStdString();
    qDebug() << QString::fromStdString(cipherText);

    this->PlainText = Hill_Decryption(cipherText);
    return true;
}


int Classic_Hill::isInvertible(std::vector<std::vector<int>> matrix, int n) {
    int det = 0;
    vector<vector<int>> submatrix(n,vector<int>(n,0));
    if(n == 1)
        return matrix[0][0];

    if (n == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x) continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det += (pow(-1, x) * matrix[0][x]* isInvertible(submatrix, n - 1));
        }
    }
    return det;
}

vector<vector<int>> Classic_Hill::inverseMatrix(){
    int det = isInvertible(Matrix, MatrixSize);
    qDebug() << det;
    int invDet = modInverse(det,26);
    vector<vector<int>> nmatrix (MatrixSize, vector<int>(MatrixSize));
    if(det != 0) {
        for(int i = 0; i < MatrixSize; i++) {
            for(int j = 0; j < MatrixSize; j++){
                nmatrix[i][j] = (calcuCofactor(j, i)*invDet)%26;
            }
        }
    }
    return nmatrix;
}

int Classic_Hill::calcuCofactor(int i, int j){
    int cofactor;
    vector<vector<int>> matrix_1 (MatrixSize-1, vector<int>(MatrixSize-1));
    for(int k = 0; k<MatrixSize-1; k++)
    {
        for(int e = 0; e<MatrixSize-1; e++)
        {
            if(k < i && e < j)
                matrix_1[k][e] = Matrix[k][e];
            else if(k < i && e >= j)
                matrix_1[k][e] = Matrix[k][e+1];
            else if(k >= i && e < j)
                matrix_1[k][e] = Matrix[k+1][e];
            else if(k >= i && e>= j)
                matrix_1[k][e] = Matrix[k+1][e+1];
        }
    }
    cofactor = isInvertible(matrix_1, MatrixSize-1);
    return cofactor*(((i+j)%2 == 0)?1:-1);
}

int Classic_Hill::modInverse(int a, int m){
    a=a%m;
    for(int x=-m;x<m;x++)
        if((a*x)%m==1) return x;
    return -1;
}
