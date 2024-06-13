#include "diarydetail.h"
#include "ui_diarydetail.h"

diaryDetail::diaryDetail(int diaryId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::diaryDetail)
{
    diaryDetailId=diaryId;
    ui->setupUi(this);
    getDiaryDetail(diaryId);
}

void diaryDetail::getDiaryDetail(int diaryId){
    // 确保数据库连接已打开
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open!";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM diary WHERE diaryId = :diaryId");
    query.bindValue(":diaryId", diaryId);

    if (!query.exec()) {
        qCritical() << "Database Error:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to execute query.");
        return;
    }

    if (query.next()) {
        detailDiary.diaryId = query.value("diaryId").toInt();
        detailDiary.userId = query.value("userId").toInt();
        detailDiary.title = query.value("title").toString();
        detailDiary.destination = query.value("destination").toString();

        QByteArray compressedContent = query.value("content").toByteArray();
        detailDiary.content = QString::fromUtf8(qUncompress(compressedContent));

        detailDiary.exchangeCode = query.value("exchangeCode").toString();
        detailDiary.point = query.value("point").toFloat();
        detailDiary.browse = query.value("browse").toInt();
        detailDiary.time = query.value("time").toDateTime();
    } else {
        qWarning() << "No entry found with diaryId:" << diaryId;
        QMessageBox::warning(this, "Not Found", "No diary entry found with the provided ID.");
        return;
    }

    // DEBUG: 输出内容以检查是否正确解压
    qDebug() << detailDiary.content;

    // 更新UI
    ui->titleLabel->setText(detailDiary.title);
    ui->destinationLabel->setText(detailDiary.destination);
    ui->pointLabel->setText("评分: " + QString::number(detailDiary.point));
    ui->browseLabel->setText("浏览量: " + QString::number(detailDiary.browse));
    ui->contentBrowser->setText(detailDiary.content);
    ui->timeLabel->setText("撰写时间:"+detailDiary.time.toString("yyyy年M月d日"));
}
int diaryDetail::givePoint(int diaryId, float newPoint) {
    if(pointCount==1){
        return 2;
    }
    else{
        QSqlQuery query;
        query.prepare("SELECT point FROM diary WHERE diaryId = :id");
        query.bindValue(":id", diaryId);
        if (!query.exec()) {
            qDebug() << "Error executing query: " << query.lastError().text();
            return 0;
        }

        if (query.next()) {
            float originalPoint = query.value(0).toFloat();
            float updatedPoint = originalPoint * 0.98 + newPoint * 0.02;

            query.prepare("UPDATE diary SET point = :newPoint WHERE diaryId = :id");
            query.bindValue(":newPoint", updatedPoint);
            query.bindValue(":id", diaryId);

            if (!query.exec()) {
                qDebug() << "Error updating point: " << query.lastError().text();
                return 0;
            }
            pointCount=1;
            return 1; // 成功更新
        } else {
            qDebug() << "No diary found with id: " << diaryId;
            return 0;
        }
    }

}
diaryDetail::~diaryDetail()
{
    delete ui;
}

void diaryDetail::on_submitPointButton_clicked()
{
    float newPoint=ui->pointSpin->text().toInt();
    if(newPoint>=0&&newPoint<=10){
        int result = givePoint(diaryDetailId, newPoint);
        if (result==1) {
            qDebug() << "Point updated successfully";
            QMessageBox::information(this, "评分成功！", "感谢您的评分!");
        }
        else if(result==2){
            QMessageBox::information(this, "已评分！", "您已经评过分了哦~");
        }
        else {
            qDebug() << "Failed to update point";
        }
    }
    else{
        QMessageBox::information(this, "评分错误", "评分应为0-10分");
    }
}

