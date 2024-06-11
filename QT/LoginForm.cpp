#include "LoginForm.h"
#include "MapWidget.h"

void LoginForm::submitClicked() {
    QString username = usernameLineEdit->text();
    QString email = emailLineEdit->text();
    QString password = passwordLineEdit->text();
    QString confirmPassword = confirmPasswordLineEdit->text();

    if (username.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all fields.");
    }
    else if (password != confirmPassword) {
        QMessageBox::warning(this, "Error", "Passwords do not match.");
    }
    else {
        // Here you can add code to process the login, such as sending data to a server or validating locally
        QMessageBox::information(this, "Success", "Login successful!");
        close(); // Close the login widget

        QMainWindow *mapWindow = new QMainWindow;
        mapWindow->setWindowTitle("Map with 200 points and 500 lines");
        MapWidget *map = new MapWidget(mapWindow);
        mapWindow->setCentralWidget(map);
        mapWindow->show();
    }
}

void LoginForm::setupUI() {
    titleLabel = new QLabel("Login Form");
    usernameLabel = new QLabel("Username:");
    usernameLineEdit = new QLineEdit;
    emailLabel = new QLabel("Email:");
    emailLineEdit = new QLineEdit;
    passwordLabel = new QLabel("Password:");
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordLabel = new QLabel("Confirm Password:");
    confirmPasswordLineEdit = new QLineEdit;
    confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    submitButton = new QPushButton("Submit");
    connect(submitButton, &QPushButton::clicked, this, &LoginForm::submitClicked);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(titleLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(emailLabel);
    layout->addWidget(emailLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(confirmPasswordLabel);
    layout->addWidget(confirmPasswordLineEdit);
    layout->addWidget(submitButton);

    setLayout(layout);
    setWindowTitle("Login Form");
}
