#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <vector>
#include <string>

class BigInteger
{
public:
    typedef long long long_t;
    typedef unsigned base_t;
    BigInteger(): is_negative(false) {data.push_back(0); }  //默认为0
    BigInteger(const BigInteger &);     //利用给定的大整数初始化
    BigInteger(const std::string &);    //利用给定的十六进制字符串初始化
    BigInteger(const long_t &);         //利用给定的long_t类型数据初始化
    ~BigInteger() {}

    BigInteger add(const BigInteger &);     //大整数加法
    BigInteger subtract(const BigInteger &);    //大整数减法
    BigInteger multiply(const BigInteger &) const;  //大整数乘法
    BigInteger divide(const BigInteger &);      //大整数整除
    BigInteger remainder(const BigInteger &);   //大整数取余
    BigInteger mod(const BigInteger &);         //大整数取模
    BigInteger divideAndremainder(const BigInteger &, BigInteger &);    //大整数整除和取余
    BigInteger pow(const BigInteger &);     //大整数幂乘
    BigInteger modAndpow(const BigInteger &, const BigInteger &) const; //大整数幂模
    BigInteger modAndinverse(const BigInteger &);   //用扩展欧几里得算法求乘法逆元

    BigInteger shiftLeft(const unsigned);   //移位运算，左移
    BigInteger shiftRight(const unsigned);  //移位运算，右移

    int compareTo(const BigInteger &) const;    //比较运算
    bool equals(const BigInteger &) const;      //判断两数是否相等
    static BigInteger valueOf(const long_t &);  //将给定数转换成大整数并返回
    std::string toString() const;   //将大整数转换为十六进制字符串
    BigInteger abs() const;         //求大整数的绝对值

protected:
    // 以下运算符重载函数主要用于像基本类型一样使用大整数类型
    friend BigInteger operator + (const BigInteger &, const BigInteger &);
    friend BigInteger operator - (const BigInteger &, const BigInteger &);
    friend BigInteger operator * (const BigInteger &, const BigInteger &);
    friend BigInteger operator / (const BigInteger &, const BigInteger &);
    friend BigInteger operator % (const BigInteger &, const BigInteger &);
    friend bool operator < (const BigInteger &, const BigInteger &);
    friend bool operator > (const BigInteger &, const BigInteger &);
    friend bool operator == (const BigInteger &, const BigInteger &);
    friend bool operator <= (const BigInteger &, const BigInteger &);
    friend bool operator <= (const BigInteger &, const BigInteger &);
    friend bool operator != (const BigInteger &, const BigInteger &);

    //重载版本，使其能够用于long_t类型
    friend BigInteger operator + (const BigInteger &, const long_t &);
    friend BigInteger operator - (const BigInteger &, const long_t &);
    friend BigInteger operator * (const BigInteger &, const long_t &);
    friend BigInteger operator / (const BigInteger &, const long_t &);
    friend BigInteger operator % (const BigInteger &, const long_t &);
    friend bool operator < (const BigInteger &, const long_t &);
    friend bool operator > (const BigInteger &, const long_t &);
    friend bool operator == (const BigInteger &, const long_t &);
    friend bool operator <= (const BigInteger &, const long_t &);
    friend bool operator <= (const BigInteger &, const long_t &);
    friend bool operator != (const BigInteger &, const long_t &);

    BigInteger operator = (const std::string & str) { return (*this) = BigInteger(str); }
    BigInteger operator = (const long_t & num) { return (*this) = BigInteger(num); }

private:
    BigInteger trim();      //去掉高位没有用的0
    int hexToNum(char);     //十六进制->十进制

public:
    static const int base_bit = 5;      //2^5 = 32，大整数每位存储的二进制数
    static const int base_char = 8;     //组成大整数的一位需要的十六进制数
    static const int base_int = 32;     //大整数一位对应的二进制位数
    static const int base_num = 0xffffffff; //截取低位的辅助（后32位）
    static const int base_temp = 0x1f;  //截取mod32的余数的辅助
    static const BigInteger ZERO;   //大整数常量0
    static const BigInteger ONE;    //大整数常量1
    static const BigInteger TWO;    //大整数常量2
    static const BigInteger TEN;    //大整数常量10

private:
    bool is_negative;   //是否为负数
    std::vector<base_t> data;   //按位数据进行存储。低位在前，高位在后

    //便于大整数运算的二进制处理类
    class bit{
    public:
        bit(const BigInteger &);    //根据大整数初始化

        size_t size() { return length; }    //返回大整数对应的二进制位数
        bool at(size_t);    //返回第i位二进制是否为1
    private:
        std::vector<base_t> bit_vector;     //二进制数据存储，每一个元素对应32位二进制
        size_t length;  //二进制的总位数
    };
    friend class Modern_RSA;   //设置RSA作为其友元类
};

#endif // BIGINTEGER_H
