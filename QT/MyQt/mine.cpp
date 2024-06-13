#include "mine.h"
#include "ui_mine.h"

mine::mine(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mine)
{
    ui->setupUi(this);
}

mine::~mine()
{
    delete ui;
}

void mine::on_diaryButton_clicked()
{


}

