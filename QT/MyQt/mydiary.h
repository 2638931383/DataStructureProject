#ifndef MYDIARY_H
#define MYDIARY_H

#include"allClass.h"
namespace Ui {
class myDiary;
}

class myDiary : public QWidget
{
    Q_OBJECT

public:
    explicit myDiary(QWidget *parent = nullptr);
    ~myDiary();
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

    void onSearchTextChanged(const QString &text);

private slots:
    void on_allPushButton_clicked();

    void on_popularityPushButton_clicked();

    void on_browsePushButton_clicked();

    void on_searchPushButton_clicked();

    void on_uploadPushButton_clicked();

private:
    Ui::myDiary *ui;
    int page=0;
    QVector<diaryInfo> diaryInfoList;
    QVector<diaryInfo> diaryInfoListShow;
    QVBoxLayout *layout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout;
    QVector<QLabel*> titleLabels;
    QVector<QLabel*> contentLabels;
    QVector<QLabel*> timeLabels;
    QVector<QLabel*> pointLabels;
    QVector<QLabel*> destinationLabels;
    QVector<QLabel*> browseLabels;
    QVector<QPushButton*> buttons;
    QVector<QFrame*> lines;
    QString searchInput="";
    int isSearch=0;
    QString initialStyleSheet="background-color: rgb(255, 255, 255); border-radius: 2px;border: 1px solid rgba(124, 124, 124,60);";
    QString seletcedStyleSheet="background-color: rgba(85, 178, 250,30); border-radius: 2px;border:1px solid rgb(85, 167, 250);";
};

#endif // MYDIARY_H
