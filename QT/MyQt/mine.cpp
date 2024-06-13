#include "mine.h"
#include "ui_mine.h"
#include"changepassword.h"
#include"changeUserName.h"
#include"Login.h"
#include"uploaddiary.h"
#include"myDiary.h"
mine::mine(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mine)
{
    qDebug()<<MySQL_Operate::userID;
    ui->setupUi(this);
    getUserName(MySQL_Operate::userID);
    ui->userNameLabel->setText(userName);
    ui->accountLabel->setText("我的ID:"+QString::number(MySQL_Operate::userID));
}
void mine::getUserName(int ID)
{

    // 创建查询对象
    QSqlQuery query;
    query.prepare("SELECT Name FROM user WHERE ID = :id");
    query.bindValue(":id", ID);

    // 执行查询
    if (query.exec()) {
        if (query.next()) {
            userName = query.value(0).toString();
        } else {
            qDebug() << "No user found with ID" << ID;
        }
    } else {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }
    // 返回结果
}

mine::~mine()
{
    delete ui;
}

void mine::on_diaryButton_clicked()
{


}


void mine::on_changePasswordButton_clicked()
{
    changePassword *tochangePWD = new changePassword;
    tochangePWD->show();
}


void mine::on_changeNameButton_clicked()
{
    changeUserName *tochangeName = new changeUserName;
    tochangeName->show();
}


void mine::on_uploadPushButton_clicked()
{
    uploadDiary *upload = new uploadDiary;
    upload->show();
}


void mine::on_myDiaryButton_clicked()
{
    myDiary *toMyDiary=new myDiary;
    toMyDiary->show();
}


// void mine::on_feedbackButton_clicked()
// {

// }

