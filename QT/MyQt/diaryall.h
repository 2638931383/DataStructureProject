#ifndef DIARYALL_H
#define DIARYALL_H
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
namespace Ui {
class diaryAll;
}

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

class diaryAll : public QWidget
{
    Q_OBJECT

public:
    explicit diaryAll(QWidget *parent = nullptr);
    ~diaryAll();
public:
    QVector<diaryInfo> getAllDiary();

    int showDiaryAll();

    void createDiaryEntries();

    void showDiaryDetail();

private slots:
    void on_allPushButton_clicked();

private:
    Ui::diaryAll *ui;
private:
    int page=0;
    QVector<diaryInfo> diaryInfoList;
    QVector<diaryInfo> diaryInfoListShow;
    QVBoxLayout *layout;
    QHBoxLayout *horizontalLayout;
};



#endif // DIARYALL_H
