#include "diarydetail.h"
#include "ui_diarydetail.h"

diaryDetail::diaryDetail(int diaryId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::diaryDetail)
{
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
}

diaryDetail::~diaryDetail()
{
    delete ui;
}
