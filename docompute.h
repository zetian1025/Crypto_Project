#ifndef DOCOMPUTE_H
#define DOCOMPUTE_H

#include <QString>

//处理加密解密信息的类。选择加密解密方法、获取加密后/解密后的信息均直接使用此类。

class DoCompute
{
    int codeIndex;      //加密解密方法的序号
    int RSAIndex;       //RSA密钥长度
    int mode;           //加密模式或是解密模式（0， 1）
    QString InputText;  //输入的待加密/解密的字符串。
    QString InputText_key;  //输入的可能会需要的key值。
    QString OutputText; //运算完后生成的待使用的字符串。

    QString RSA_Public;
    QString RSA_Private;
    QString RSA_bigN;

public:
    DoCompute();
    int DoComputeNow(bool is_key_added);    //本函数为加密解密的核心函数。
    inline int vaild(); //判断用户在按下start按钮时是否有非法输入。

    void setcodeIndex(int index);
    void setRSAIndex(int index);
    void setMode(int mode);
    void setInputText(QString text);
    void setInputText_key(QString text);
    void setOutputText(QString text);

    void doRSAinit();

    int getcodeIndex();
    int getRSAIndex();
    int getMode();
    QString getInputText();
    QString getInputText_key();
    QString getOutputText();
    QString getRSA_Public();
    QString getRSA_Private();
    QString getRSA_bigN();
};

#endif // DOCOMPUTE_H
