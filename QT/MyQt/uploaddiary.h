#ifndef UPLOADDIARY_H
#define UPLOADDIARY_H

#include"allClass.h"

namespace Ui {
class uploadDiary;
}


class uploadDiary : public QWidget
{
    Q_OBJECT

public:
    explicit uploadDiary(QWidget *parent = nullptr);
    ~uploadDiary();
    int uploadNewDiary(int diaryId, int userId, const QString &title, const QString &destination, const QByteArray  &content, const QString &exchangeCode);

private slots:
    void on_uploadPushButton_clicked();

private:
    Ui::uploadDiary *ui;
};

#endif // UPLOADDIARY_H
