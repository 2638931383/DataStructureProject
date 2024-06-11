#include "Register.h"
#include "ui_Register.h"

//get random ID
QString getRandomID()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString number = time.toString("ddhhmmss"); //设置显示格式
    QTime t;
    t= QTime::currentTime();
    srand(t.msec()+t.second()*100);
    int n = rand() % 100;
    return number+QString("%1").arg(n);//添加一个随机数
}



Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    // Load picture
    QPixmap pix(":/Login2.jpg");

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
    shadow->setOffset(-1, 0);
    shadow->setColor(QColor("#888888"));
    shadow->setBlurRadius(100);
    ui->image->setGraphicsEffect(shadow);
}

Register::~Register()
{
    delete ui;
}

void Register::on_sign_up_clicked()
{
    QString name = ui->name->text();
    QString password = ui->password->text();
    QString surepass = ui->password_->text();
    QString ID = getRandomID();
    //random ID



    //judge
    if(password == surepass)
    {
        QString sql = QString("insert into user(ID,name,password) values('%1','%2','%3');").arg(ID.toInt()).arg(name).arg(password);
        QSqlQuery query;
        if(!query.exec(sql))
        {
            qDebug()<<"Sign UP error";
            QMessageBox::information(this,"Sign Up","Sorry, there are some mistakes.");
        }
        else
        {
            qDebug()<<"Sign UP successfully";
            QMessageBox::information(this,"Sign Up","Sign up successfully."+tr("Your ID is %1").arg(ID));
            Login *Log = new Login;
            Log->show();
            this->close();
        }

    }else{
        QMessageBox::information(this,"Sign Up","Inconsistency between two password entries.");
    }
}


void Register::on_back_clicked()
{
    Login *Log = new Login;
    Log->show();
    this->close();
}

