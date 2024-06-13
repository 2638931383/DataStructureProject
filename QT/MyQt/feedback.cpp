#include "feedback.h"
#include "ui_feedback.h"

feedback::feedback(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::feedback)
{
    ui->setupUi(this);
}
int feedback::submitFeedback(const QString &content) {
    // 获取当前时间
    QDateTime currentTime = QDateTime::currentDateTime();
    // 获取当前用户ID
    int userId = MySQL_Operate::userID;

    // 准备插入查询
    QSqlQuery query(db);
    query.prepare("INSERT INTO feedback (userId, content, time) VALUES (:userId, :content, :time)");
    query.bindValue(":userId", userId);
    query.bindValue(":content", content);
    query.bindValue(":time", currentTime.toString("yyyy-MM-dd HH:mm:ss"));

    // 执行查询
    if (!query.exec()) {
        qDebug() << "Failed to insert feedback:" << query.lastError().text();
        return -1;
    }

    return 0;  // 成功
}
feedback::~feedback()
{
    delete ui;
}

void feedback::on_submitButton_clicked()
{
    QString inputContentt=ui->textEdit->toPlainText();
    if(submitFeedback(inputContentt)==0){
         QMessageBox::information(this, "ok", "反馈成功");
    }else{
        QMessageBox::warning(this, "ok", "反馈失败");
    }
}

