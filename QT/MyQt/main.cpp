#include "mainwindow.h"
#include "ui_Login.h"
#include <QApplication>
#include "Login.h"
#include "MySQL_Operate.h"
#include "Register.h"
#include "MapANDOptions.h"
#include"diaryall.h"
#include "bupt.h"
int main(int argc, char *argv[])
{
    Init_Database();
    QApplication a(argc, argv);
    bupt M;

     M.show();
    return a.exec();
}
