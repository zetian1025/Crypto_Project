#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "docompute.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    DoCompute myCompute;
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_ComboBox_Crypto_currentIndexChanged(int index);

    void on_RadioBtn_Encryption_clicked();

    void on_RadioBtn_Decryption_clicked();

    void on_pushButton_RSA_Generate_clicked();

    void on_comboBox_RSA_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
