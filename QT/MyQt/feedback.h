#ifndef FEEDBACK_H
#define FEEDBACK_H

#include"allClass.h"

namespace Ui {
class feedback;
}

class feedback : public QWidget
{
    Q_OBJECT

public:
    explicit feedback(QWidget *parent = nullptr);
    ~feedback();
public:
    int submitFeedback(const QString &content);
private slots:
    void on_submitButton_clicked();

private:
    Ui::feedback *ui;
};

#endif // FEEDBACK_H
