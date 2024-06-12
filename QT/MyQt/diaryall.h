#ifndef DIARYALL_H
#define DIARYALL_H

#include"allClass.h"
namespace Ui {
class diaryAll;
}



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

    int showPopularityDiaryAll();

    void updateDiaryEntries();

private slots:
    void on_allPushButton_clicked();

    void on_uploadPushButton_clicked();

    void on_popularityPushButton_clicked();

private:
    Ui::diaryAll *ui;
private:
    int page=0;
    QVector<diaryInfo> diaryInfoList;
    QVector<diaryInfo> diaryInfoListShow;
    QVBoxLayout *layout;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QLabel *contentLabel;
    QPushButton *button;
};



#endif // DIARYALL_H
