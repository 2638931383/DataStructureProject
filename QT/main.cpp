//#include "LoginForm.h"
#include <QApplication>

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LoginForm loginForm;
    loginForm.show();

    return app.exec();
}
