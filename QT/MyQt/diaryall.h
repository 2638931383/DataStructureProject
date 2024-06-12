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

    int showBrowseDiaryAll();

    void updateAllDiaryEntries();

    void updateDiaryEntries();

    bool customContains(const QString &str, const QString &subStr);

    int searchDiary(const QString &searchInput);
private slots:
    void on_allPushButton_clicked();

    void on_uploadPushButton_clicked();

    void on_popularityPushButton_clicked();

    void on_browsePushButton_clicked();

    void on_searchPushButton_clicked();

private:
    Ui::diaryAll *ui;
private:
    int page=0;
    QVector<diaryInfo> diaryInfoList;
    QVector<diaryInfo> diaryInfoListShow;
    QVBoxLayout *layout;
    QHBoxLayout *horizontalLayout;
    QVector<QLabel*> titleLabels;
    QVector<QLabel*> contentLabels;
    QVector<QPushButton*> buttons;
    QVector<QFrame*> lines;
};



#endif // DIARYALL_H
