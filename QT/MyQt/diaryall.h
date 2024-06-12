#ifndef DIARYALL_H
#define DIARYALL_H

#include"allClass.h"
namespace Ui {
class diaryAll;
}



class diaryAll : public QWidget
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event) override {
        // 在这里执行必要的清理工作
        qDebug() << "DiaryDetail is closing";

        // 手动释放UI资源（如果有）
        // 例如：delete widgetPointer;

        // 调用基类的closeEvent以确保正常关闭
        QWidget::closeEvent(event);

        // 如果希望窗口关闭后自动销毁对象，可以使用：
        delete this;
    }
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

    void onSearchTextChanged(const QString &text);

    void refresh();
private slots:
    void on_allPushButton_clicked();

    void on_uploadPushButton_clicked();

    void on_popularityPushButton_clicked();

    void on_browsePushButton_clicked();

    void on_searchPushButton_clicked();

    void on_refreshPushButton_clicked();

    void on_mineButton_clicked();

private:
    Ui::diaryAll *ui;
private:
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



#endif // DIARYALL_H
