#ifndef MYSQL_OPERATE_H
#define MYSQL_OPERATE_H

#include <QSqlDatabase> //数据驱动
#include <QSqlQuery> //数据库执行语句

//链接数据库
extern QSqlDatabase db;

void Init_Database(void);
#endif // MYSQL_OPERATE_H
