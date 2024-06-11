#include "Login.h"
#include "ui_Login.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    // Load picture
    QPixmap pix(":/Login1.jpg");

    // Check if the picture loaded successfully
    if (pix.isNull()) {
        qDebug() << "Failed to load image.";
        return;
    }

    // Scale the picture to fit the label
    QSize size = ui->image->size();
    ui->image->setPixmap(pix.scaled(size));


    //set shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setColor(QColor("#888888"));
    shadow->setBlurRadius(30);
    ui->image->setGraphicsEffect(shadow);
}

Login::~Login()
{
    delete ui;
}

void Login::on_Login__clicked()
{
    QString ID = ui->ID->text();
    QString Password = ui->Password->text();
    QString sql = QString("select * from user where ID='%1' and password='%2'").arg(ID).arg(Password);
    QSqlQuery query(sql);
    if(!query.next())
    {
        qDebug()<<"Login error";
        QMessageBox::information(this,"Login","Error,ID or Password mistakes.");
    }
    else
    {
        qDebug()<<"Login success";
        QMessageBox::information(this,"Login","Login sucessfully.");
        MapANDOptions *M = new MapANDOptions;                                        //Login sucessfully
        M->show();
        this->close();
    }
}


void Login::on_Register_clicked()
{
    Register *SignUp = new Register;
    SignUp->show();
    this->close();
}

