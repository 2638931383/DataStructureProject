#include "changepassword.h"
#include "ui_changepassword.h"

changePassword::changePassword(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::changePassword)
{
    getPassword(MySQL_Operate::userID);
    ui->setupUi(this);
}
int changePassword::changePWD(int ID, const QString &password)
{
    // 创建查询对象
    QSqlQuery query;
    query.prepare("UPDATE user SET password = :password WHERE ID = :id");
    query.bindValue(":password", password);
    query.bindValue(":id", ID);
    // 执行更新操作
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return -2; // 返回错误码 -2 表示查询执行失败
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "No user found with ID" << ID;
        return -3; // 返回错误码 -3 表示没有找到对应的用户
    }
    // 返回 0 表示成功
    return 0;
}
void changePassword::getPassword(int ID)
{

    // 创建查询对象
    QSqlQuery query;
    query.prepare("SELECT password FROM user WHERE ID = :id");
    query.bindValue(":id", ID);

    // 执行查询
    if (query.exec()) {
        if (query.next()) {
            oldPWD = query.value(0).toString();
        } else {
            qDebug() << "No user found with ID" << ID;
        }
    } else {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }
    // 返回结果
}

changePassword::~changePassword()
{
    delete ui;
}

void changePassword::on_sureButton_clicked()
{
    inputPWD=ui->beforePWD->text();
    newPWD=ui->firstPWD->text();
    surePWD=ui->secondPWD->text();
    if(inputPWD!=oldPWD){
        QMessageBox::warning(this, "密码错误", "原密码错误!");

    }
    else{
        if(newPWD!=surePWD){
            QMessageBox::warning(this, "密码错误", "两次密码不一致!");
        }
        else{
            if(newPWD.length()<=3||newPWD.length()>=15){
               QMessageBox::warning(this, "密码错误", "长度错误!");
            }
            else{
                if(changePWD(MySQL_Operate::userID,surePWD)==0){
                    QMessageBox::information(this, "修改成", "密码修改成功!");
                    ui->beforePWD->setText("");
                    ui->firstPWD->setText("");
                    ui->secondPWD->setText("");
                    this->close();
                }

                else{
                    QMessageBox::warning(this, "密码错误", "系统繁忙~");
                }
            }
        }

    }
}

