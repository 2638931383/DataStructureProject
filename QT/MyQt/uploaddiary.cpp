#include "uploaddiary.h"
#include "ui_uploaddiary.h"
#include "MySQL_Operate.h"

uploadDiary::uploadDiary(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::uploadDiary)
{
    ui->setupUi(this);
}
int uploadDiary::uploadNewDiary(int diaryId, int userId, const QString &title, const QString &destination, const QByteArray &content, const QString &exchangeCode) {

    QSqlQuery query(db);
    query.prepare("INSERT INTO diary (diaryId, userId, title, destination, content, exchangeCode, time, point, browse) "
                  "VALUES (:diaryId, :userId, :title, :destination, :content, :exchangeCode, :time, :point, :browse)");
    query.bindValue(":diaryId", diaryId);
    query.bindValue(":userId", userId);
    query.bindValue(":title", title);
    query.bindValue(":destination", destination);
    query.bindValue(":content", content);
    query.bindValue(":exchangeCode", exchangeCode);
    query.bindValue(":time", QDateTime::currentDateTime());
    query.bindValue(":point", 5.0f);
    query.bindValue(":browse", 1);

    if (!query.exec()) {
        qWarning() << "Failed to execute query:" << query.lastError().text();
        return 0;
    }

    return 1;
}
uploadDiary::~uploadDiary()
{
    delete ui;
}

void uploadDiary::on_uploadPushButton_clicked()
{
    diaryInfo inputDiary;
    inputDiary.userId=0;
    inputDiary.title=ui->titleLineEdit->text();
    inputDiary.destination=ui->destinationLineEdit->text();
    inputDiary.content=ui->contentTextEdit->toPlainText();
    QByteArray tempContent = inputDiary.content.toUtf8();
    // 压缩数据
    QByteArray compressedContent = qCompress(tempContent, -1); // 使用默认压缩级别
    if(inputDiary.title==""){
        QMessageBox::information(this, "Upload", "标题不可为空");
    }
    else if(inputDiary.destination==""){
        QMessageBox::information(this, "Upload", "目的地不可为空");
    }
    else if(inputDiary.content==""){
        QMessageBox::information(this, "Upload", "日记内容不可为空");
    }
    else{
        if(uploadNewDiary(0,inputDiary.userId,inputDiary.title,inputDiary.destination,compressedContent,"exchangeCode0")==1){
            QMessageBox::information(this, "Upload", "Diary uploaded successfully");

        }
        else{
            QMessageBox::warning(this, "Upload", "Failed to upload diary");
        }
    }

    ui->titleLineEdit->setText("");
    ui->destinationLineEdit->setText("");
    ui->contentTextEdit->clear();
    inputDiary.title="";
    inputDiary.destination="";
    inputDiary.content="";
}

