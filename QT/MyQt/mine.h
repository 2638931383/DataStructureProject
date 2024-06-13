#ifndef MINE_H
#define MINE_H

#include <QWidget>
#include"allClass.h"
namespace Ui {
class mine;
}

class mine : public QWidget
{
    Q_OBJECT

public:
    explicit mine(QWidget *parent = nullptr);
    ~mine();
public:
    void getUserName(int ID);

private slots:
    void on_diaryButton_clicked();

    void on_changePasswordButton_clicked();

    void on_changeNameButton_clicked();

    void on_uploadPushButton_clicked();

    void on_myDiaryButton_clicked();

    void on_feedbackButton_clicked();

    void on_navigatorButton_clicked();

    void on_diaryButton_2_clicked();

private:
    Ui::mine *ui;
    QString userName="";
    int page[4]={0};
};

#endif // MINE_H
