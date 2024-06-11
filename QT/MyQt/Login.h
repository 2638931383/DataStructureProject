#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QSqlDatabase> //数据驱动
#include <QSqlQuery> //数据库执行语句
#include <QMessageBox>//消息盒子
#include <QDebug>
#include <QString>
#include "Register.h"
#include "MapANDOptions.h"
void sqlite_Init();
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:

    void on_Login__clicked();

    void on_Register_clicked();

private:
    Ui::Login *ui;
};



#endif // LOGIN_H
