#include "mainwindow.h"
#include "ui_Login.h"
#include <QApplication>
#include "Login.h"
#include "MySQL_Operate.h"
#include "Register.h"
#include "MapANDOptions.h"
#include"diaryall.h"
#include "bupt.h"
#include"mine.h"
int main(int argc, char *argv[])
{
    Init_Database();
    QApplication a(argc, argv);
<<<<<<< HEAD
    // bupt M;
    Login L;
    // diaryAll D;
    // mine Mine;
    // Mine.show();
    // D.show();
    L.show();
    // M.show();
=======
    bupt M;
    //Login L;
    MapANDOptions m;
    //m.show();
    M.show();

    //diaryAll D;
    //mine Mine;
    //Mine.show();
    // D.show();
    //L.show();
     // M.show();
>>>>>>> b23e2697cac94313400fb59a701be5770bc383aa
    return a.exec();
}
