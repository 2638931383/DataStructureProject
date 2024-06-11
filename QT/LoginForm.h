#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMainWindow>

class LoginForm : public QWidget {
    Q_OBJECT

public:
    LoginForm(QWidget *parent = nullptr) : QWidget(parent) {
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

#endif // LOGINFORM_H
