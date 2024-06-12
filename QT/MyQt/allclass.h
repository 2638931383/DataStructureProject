#ifndef ALLCLASS_H
#define ALLCLASS_H

#include <QWidget>
#include <QWidget>
#include <QtSql>
#include <QDateTime>
#include <QMessageBox>//消息盒子
#include <QByteArray>
#include <QDebug>
#include <QtGlobal> // 包含 qint64 类型
#include <QString>
#include <QVector>
#include <QStringListModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QListView>
#include <QMainWindow>
#include<QListWidget>
#include <QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include <algorithm>
#include "MySQL_Operate.h"

class allClass : public QWidget
{
    Q_OBJECT
public:
    explicit allClass(QWidget *parent = nullptr);

signals:
};
class diaryInfo{
public:
    int diaryId;
    int userId;
    QString title;
    QString destination;
    QString  content;
    QString exchangeCode;
    float point;
    int browse;
    QDateTime time;
};

#endif // ALLCLASS_H
