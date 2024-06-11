#ifndef REGISTER_H
#define REGISTER_H
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QSqlDatabase> //数据驱动
#include <QSqlQuery> //数据库执行语句
#include <QMessageBox>//消息盒子
#include <QDebug>
#include <QString>
#include "Login.h"
#include <QRandomGenerator>
#include <QDatetime.h>
#include <QTime>
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    Register(QWidget *parent = nullptr);
    ~Register();

private slots:


    void on_sign_up_clicked();

    void on_back_clicked();

private:
    Ui::Register *ui;
};


QString getRandomID();

#endif // REGISTER_H
