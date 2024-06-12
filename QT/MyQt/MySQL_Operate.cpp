#include "MySQL_Operate.h"

QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

void Init_Database(void)
{


    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("252211034");
    db.setDatabaseName("dts");
    if(!db.open()){
        qDebug() << "未成功链接到数据库";
    }
    else{
        qDebug() << "成功链接到数据库";
    }

}
