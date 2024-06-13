#ifndef MYDIARYDETAIL_H
#define MYDIARYDETAIL_H

#include <allClass.h>

namespace Ui {
class myDiaryDetail;
}
class myDiaryDetail : public QDialog

{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event) override {
        // 在这里执行必要的清理工作
        qDebug() << "DiaryDetail is closing";

        // 手动释放UI资源（如果有）
        // 例如：delete widgetPointer;

        // 调用基类的closeEvent以确保正常关闭
        QWidget::closeEvent(event);

        // 如果希望窗口关闭后自动销毁对象，可以使用：
        delete this;
    }
public:
    explicit myDiaryDetail(int diaryId, QWidget *parent = nullptr);
    ~myDiaryDetail();
public:
    void getDiaryDetail(int diaryId);
    int deleteDiary(int diaryId);
private slots:


    void on_deleteDiaryButton_clicked();

private:
    diaryInfo detailDiary;
    int diaryDetailId;
    int pointCount=0;
private:
    Ui::myDiaryDetail *ui;
};

#endif // MYDIARYDETAIL_H
