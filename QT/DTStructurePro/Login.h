#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMainWindow>

class Login : public QWidget {
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
        submitClicked();
    }
public:
    void setupUI();
public slots:
    void submitClicked();

private:
    QLabel *titleLabel;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *confirmPasswordLabel;
    QLineEdit *confirmPasswordLineEdit;
    QPushButton *submitButton;

};

#endif // LOGIN_H
