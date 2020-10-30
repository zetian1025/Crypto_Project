#include "widget.h"
#include "ui_widget.h"
#include "CodeException.h"
#include <time.h>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->TextEdit_Input->setPlaceholderText("待加密的明文或待加密的密文");
    ui->TextEdit_Input_Key->setPlaceholderText("可能会需要的key值（若需要且没有输入将会随机生成）");
    ui->TextEdit_RSA_public->setPlaceholderText("这里将会生成RSA算法中的公钥");
    ui->TextEdit_RSA_private->setPlaceholderText("这里将会生成RSA算法中的私钥");
    ui->TextEdit_RSA_bigN->setPlaceholderText("这里将会生成RSA算法中的大N值");
}

Widget::~Widget()
{
    delete ui;
}

//按下start按钮后的事件。调用了一个DoCompute对象用于对加密解密的处理。
void Widget::on_pushButton_clicked()
{
    myCompute.setInputText(ui->TextEdit_Input->toPlainText());
    myCompute.setInputText_key(ui->TextEdit_Input_Key->toPlainText());

    int result = FAIL;

    if (ui->TextEdit_Input_Key->toPlainText() != "") {
        result = myCompute.DoComputeNow(true);
    }
    else {
        result = myCompute.DoComputeNow(false);
    }

    if (result == OK) ui->TextEdit_Output->setText(myCompute.getOutputText());
    else ui->TextEdit_Output->setText("错误代码：" + QString::number(result));
}

//用于处理combobox的函数。index为使用的加密解密算法的序号。
void Widget::on_ComboBox_Crypto_currentIndexChanged(int index)
{
    myCompute.setcodeIndex(index);
}

//加密模式的设置（0）
void Widget::on_RadioBtn_Encryption_clicked()
{
    myCompute.setMode(0);
}

//解密模式的设置（1）
void Widget::on_RadioBtn_Decryption_clicked()
{
    myCompute.setMode(1);
}

void Widget::on_pushButton_RSA_Generate_clicked()
{
    clock_t startTime = clock();
    myCompute.doRSAinit();
    clock_t endTime = clock();
    double time = (double)(endTime-startTime)/CLOCKS_PER_SEC;
    QString qsTime = QString::fromStdString(std::to_string(time));
    qsTime = qsTime.mid(0, qsTime.size()-3);

    ui->TextEdit_RSA_bigN->setText(myCompute.getRSA_bigN());
    ui->TextEdit_RSA_public->setText(myCompute.getRSA_Public());
    ui->TextEdit_RSA_private->setText(myCompute.getRSA_Private());
    ui->Label_Time->setText(qsTime + " s");
}

void Widget::on_comboBox_RSA_currentIndexChanged(int index)
{
    myCompute.setRSAIndex(index);
}
