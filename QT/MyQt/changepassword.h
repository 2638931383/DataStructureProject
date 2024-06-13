#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include "allClass.h"

namespace Ui {
class changePassword;
}

class changePassword : public QWidget
{
    Q_OBJECT

public:
    explicit changePassword(QWidget *parent = nullptr);
    ~changePassword();
public:
    int changePWD(int ID, const QString &password);
    void getPassword(int ID);

private slots:
    void on_sureButton_clicked();

private:
    Ui::changePassword *ui;
    QString inputPWD="";
    QString oldPWD="";
    QString newPWD="";
    QString surePWD="";
};

#endif // CHANGEPASSWORD_H
