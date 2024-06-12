#include "MySQL_Operate.h"

QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
void Init_Database(void)
{


    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("database1");
    if(!db.open()){
        qDebug() << "未成功链接到数据库";
    }
    else{
        qDebug() << "成功链接到数据库";
    }

}


bool toMySQL(QString my)
{
    QSqlQuery query;
    if (query.exec(my))
    {
        return true;
    }
    return false;
}
