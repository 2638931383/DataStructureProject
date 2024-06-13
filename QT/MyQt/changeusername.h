#ifndef CHANGEUSERNAME_H
#define CHANGEUSERNAME_H

#include"allClass.h"

namespace Ui {
class changeUserName;
}

class changeUserName : public QWidget
{
    Q_OBJECT

public:
    explicit changeUserName(QWidget *parent = nullptr);
    ~changeUserName();
public:
    int changeName(int ID, const QString &name);
private slots:
    void on_sureButton_clicked();

private:
    Ui::changeUserName *ui;
    QString nameInput="";
};

#endif // CHANGEUSERNAME_H
