#include "mydiarydetail.h"
#include "ui_mydiarydetail.h"

myDiaryDetail::myDiaryDetail(int diaryId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDiaryDetail)
{
    diaryDetailId=diaryId;
    ui->setupUi(this);
    getDiaryDetail(diaryId);
}
void myDiaryDetail::getDiaryDetail(int diaryId){
    // 确保数据库连接已打开

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
int myDiaryDetail::deleteDiary(int diaryId) {

    QSqlQuery query(db);
    // 准备删除语句
    query.prepare("DELETE FROM diary WHERE diaryId = :diaryId");
    query.bindValue(":diaryId", diaryId);

    // 执行删除操作
    if (query.exec()) {
        qDebug() << "Diary entry with diaryId" << diaryId << "deleted successfully.";
        QMessageBox::information(this, "delete", "666，你把我删了=_=");
        return 0; // 成功删除

    } else {
        qWarning() << "Failed to delete diary entry with diaryId" << diaryId << ":" << query.lastError();
        QMessageBox::warning(this, "delete", "删除失败");
        return -1; // 删除失败
    }
}
myDiaryDetail::~myDiaryDetail()
{
    delete ui;
}

void myDiaryDetail::on_deleteDiaryButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Delete Diary");
    msgBox.setText("你要删除我？真的假的owo");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        deleteDiary(diaryDetailId);

        this->close();

    }



}

