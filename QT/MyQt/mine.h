#ifndef MINE_H
#define MINE_H

#include <QWidget>

namespace Ui {
class mine;
}

class mine : public QWidget
{
    Q_OBJECT

public:
    explicit mine(QWidget *parent = nullptr);
    ~mine();

private slots:
    void on_diaryButton_clicked();

private:
    Ui::mine *ui;
};

#endif // MINE_H
