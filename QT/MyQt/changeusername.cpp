#include "changeusername.h"
#include "ui_changeusername.h"

changeUserName::changeUserName(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::changeUserName)
{
    ui->setupUi(this);
}
int changeUserName::changeName(int ID, const QString &name)
{
    // 创建查询对象
    QSqlQuery query;
    query.prepare("UPDATE user SET name = :name WHERE ID = :id");
    query.bindValue(":name", name);
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
changeUserName::~changeUserName()
{
    delete ui;
}

void changeUserName::on_sureButton_clicked()
{
    nameInput=ui->nameInput->text();
    if(nameInput.length()<1||nameInput.length()>10){
        QMessageBox::warning(this, "名字错误", "长度错误!");
    }
    else{
        if(changeName(MySQL_Operate::userID,nameInput)==0){
            QMessageBox::information(this, "修改成功", "修改成功!");
        }
        else{
            QMessageBox::warning(this, "warning", "系统繁忙~");
        }
    }
}

