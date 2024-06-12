#ifndef DIARYDETAIL_H
#define DIARYDETAIL_H
#include"allClass.h"

namespace Ui {
class diaryDetail;
}

class diaryDetail : public QDialog

{
    Q_OBJECT

public:
    explicit diaryDetail(int diaryId, QWidget *parent = nullptr);
    ~diaryDetail();
public:
    void getDiaryDetail(int diaryId);
private:
    diaryInfo detailDiary;
private:
    Ui::diaryDetail *ui;
};

#endif // DIARYDETAIL_H
