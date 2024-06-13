#ifndef DIARYDETAIL_H
#define DIARYDETAIL_H
#include"allClass.h"

namespace Ui {
class diaryDetail;
}

class diaryDetail : public QDialog

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
    explicit diaryDetail(int diaryId, QWidget *parent = nullptr);
    ~diaryDetail();
public:
    void getDiaryDetail(int diaryId);

    int givePoint(int diaryId, float newPoint);
private slots:
    void on_submitPointButton_clicked();

private:
    diaryInfo detailDiary;
    int diaryDetailId;
    int pointCount=0;
private:
    Ui::diaryDetail *ui;
};

#endif // DIARYDETAIL_H
