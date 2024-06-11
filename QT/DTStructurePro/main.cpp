#include <QApplication>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QPaintEvent>
#include <QDialog>
#include <QList>
#include <vector>
#include <QDebug>
#include "Login.h"
// Dummy data for demonstration
std::vector<std::pair<QString, double>> schools = {
    {"某某学校1", 2.5},
    {"某某学校2", 3.2},
    {"某某学校3", 4.0},
    // Add more schools here...
};

std::vector<QString> studyLog = {
    {"日志内容"},
    {"日志内容"},
    {"日志内容"},
    // Add more logs here...
};

QString GlobalUsername;

class LogDetailsWindow : public QDialog {
    Q_OBJECT
public:
    LogDetailsWindow(const QString& author, const QString& content, QWidget *parent = nullptr)
        : QDialog(parent), m_author(author), m_content(content)
    {
        setWindowTitle("日志详情");

        QVBoxLayout *layout = new QVBoxLayout(this);

        // 显示作者
        QLabel *authorLabel = new QLabel("作者: " + m_author, this);
        layout->addWidget(authorLabel);
        // 显示日志内容
        QTextEdit *contentTextEdit = new QTextEdit(this);
        contentTextEdit->setText(m_content);
        contentTextEdit->setReadOnly(true);
        layout->addWidget(contentTextEdit);

        setLayout(layout);
    }

private:
    QString m_author;
    QString m_content;
};

class StudyAbroadLogWindow : public QDialog {
    Q_OBJECT
public:
    StudyAbroadLogWindow(QWidget *parent = nullptr, const QList<QString>& logTitles = QList<QString>()) : QDialog(parent) {
        setFixedSize(200, 400); // 设置固定大小为 200x400
        setWindowTitle("游学日志");
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Create buttons for each log title
        for (const QString& title : logTitles) {
            QPushButton *logButton = new QPushButton(title, this);

            //设置按钮的大小策略，使其填充整个窗口
            logButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            layout->addWidget(logButton);

            // Connect the button clicked signal to a slot
            connect(logButton, &QPushButton::clicked, this, &StudyAbroadLogWindow::handleLogButtonClick);
        }
        setLayout(layout);
    }

signals:
    void logButtonClicked(const QString& logTitle);

private slots:
    void handleLogButtonClick() {
        QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
        if (senderButton) {

            QString logTitle = senderButton->text();
            QString logContent; // 根据日志标题获取日志内容，这里假设日志内容以全局变量存储
            // 根据日志标题从全局变量 studyLog 中获取日志内容
            for (const QString& log : studyLog) {
                if (log.contains(logTitle)) {
                    logContent = log;
                    break;
                }
            }
            emit logButtonClicked(logTitle);

            // 创建并显示日志详情窗口
            LogDetailsWindow *detailsWindow = new LogDetailsWindow(logTitle, logContent, this);
            detailsWindow->show(); // 显示窗口
        }
    }
};

// 新的窗口类用于显示学校的详细信息
class SchoolDetailsWindow : public QDialog {
    Q_OBJECT
public:
    SchoolDetailsWindow(const QString& schoolName, double distance, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("学校详情");
        setFixedSize(200, 200); // 设置固定大小为 200x200
        QVBoxLayout *layout = new QVBoxLayout(this);

        // 创建标签来显示学校的名称和距离
        QLabel *lblSchoolName = new QLabel(QString("学校名称：%1").arg(schoolName), this);
        QLabel *lblDistance = new QLabel(QString("距离：%1 km").arg(distance), this);

        layout->addWidget(lblSchoolName);
        layout->addWidget(lblDistance);

        setLayout(layout);
    }
};

class SchoolButton : public QPushButton {
    Q_OBJECT
public:
    SchoolButton(const QString& schoolName, double distance, QWidget *parent = nullptr) : QPushButton(parent), m_schoolName(schoolName), m_distance(distance) {
        setText(QString("学校名称：%1\n距离：%2 km").arg(m_schoolName).arg(m_distance));
        connect(this, &QPushButton::clicked, this, &SchoolButton::showDetails);
    }

signals:
    void clickedWithDetails(const QString& schoolName, double distance);

private slots:
    void showDetails() {
        emit clickedWithDetails(m_schoolName, m_distance);
    }

private:
    QString m_schoolName;
    double m_distance;
};

class RecommendationWindow : public QDialog {
    Q_OBJECT
public:
    RecommendationWindow(const std::vector<std::pair<QString, double>>& schools, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("推荐");
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Loop through each school and add buttons
        for(const auto& school : schools) {
            SchoolButton *schoolButton = new SchoolButton(school.first, school.second, this);
            layout->addWidget(schoolButton);

            // Connect SchoolButton's signal to MapWidget's slot
            connect(schoolButton, &SchoolButton::clickedWithDetails, this, &RecommendationWindow::showSchoolDetails);
        }
        setLayout(layout);
    }

private slots:
    void showSchoolDetails(const QString& schoolName, double distance) {
        // 创建新的 SchoolDetailsWindow 来显示学校的详细信息
        SchoolDetailsWindow *detailsWindow = new SchoolDetailsWindow(schoolName, distance, this);
        detailsWindow->exec(); // 显示新窗口
    }
};

class MyAccountWindow : public QDialog {
    Q_OBJECT
public:
    MyAccountWindow(QWidget *parent = nullptr) : QDialog(parent) {
        setFixedSize(200, 200); // 设置固定大小为 200x200
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *lblUsername = new QLabel("用户名: " + GlobalUsername, this); // 创建标签并显示用户名
        layout->addWidget(lblUsername); // 将标签添加到布局中

        QPushButton *btnMyLog = new QPushButton("我的日志", this);
        QPushButton *btnLogout = new QPushButton("退出登录", this);

        //设置按钮的大小，使其填充整个窗口
        btnMyLog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnLogout->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        layout->addWidget(btnMyLog);
        layout->addWidget(btnLogout);

        connect(btnMyLog, &QPushButton::clicked, this, &MyAccountWindow::showMyLog);
        connect(btnLogout, &QPushButton::clicked, this, &MyAccountWindow::logout);

        setLayout(layout);
    }

signals:
    void myLogClicked();
    void logoutClicked();

private slots:
    void showMyLog() {
        emit myLogClicked();
    }

    void logout() {
        // 关闭当前窗口并发送退出登录信号
        close();
        emit logoutClicked();
    }
};

class MapWidget : public QWidget {
    Q_OBJECT
public:
    MapWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(800, 850);

        // Create layout for buttons
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();

        // Create buttons
        QPushButton *btnMy = new QPushButton("我的", this);
        QPushButton *btnNavigation = new QPushButton("导航", this);
        QPushButton *btnDynamic = new QPushButton("动态", this);
        QPushButton *btnRecommendation = new QPushButton("推荐", this);

        // Set buttons to expand horizontally
        btnMy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        btnNavigation->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        btnDynamic->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        btnRecommendation->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        // Add buttons to layout
        buttonLayout->addWidget(btnMy);
        buttonLayout->addWidget(btnNavigation);
        buttonLayout->addWidget(btnDynamic);
        buttonLayout->addWidget(btnRecommendation);

        // Add a stretch to push buttons to the right
        buttonLayout->addStretch();

        // Add button layout to main layout
        mainLayout->addStretch();
        mainLayout->addLayout(buttonLayout);

        // Set layout for this widget
        setLayout(mainLayout);

        // Connect button click signal to slot
        connect(btnMy, &QPushButton::clicked, this, &MapWidget::showMyAccountWindow);
        connect(btnRecommendation, &QPushButton::clicked, this, [this]() {
            showRecommendation(schools);
        });
        connect(btnDynamic, &QPushButton::clicked, this, [this]() {
            showDynamicWindow(studyLog);
        });
    }

private slots:
    void showRecommendation(const std::vector<std::pair<QString, double>>& schools) {

        // Create and show recommendation window
        RecommendationWindow *recommendationWindow = new RecommendationWindow(schools, this);
        recommendationWindow->show();
    }

    void showDynamicWindow(const std::vector<QString> studyLog) {

        // Create and show study abroad log window
        QList<QString> logList(studyLog.begin(), studyLog.end());
        StudyAbroadLogWindow *studyAbroadLogWindow = new StudyAbroadLogWindow(this, logList);
        studyAbroadLogWindow->setWindowTitle("游学日志");

        // Extract log titles from studyLog
        QList<QString> logTitles;
        for (const auto& log : studyLog) {
            logTitles.append(log); // Assuming first element in pair is the log title
        }
        studyAbroadLogWindow->show();
    }

    void showMyAccountWindow() {
        MyAccountWindow *myAccountWindow = new MyAccountWindow(this);
        myAccountWindow->setWindowTitle("个人中心");
        myAccountWindow->show();
        // 连接 MyAccountWindow 的退出登录信号到槽函数
        connect(myAccountWindow, &MyAccountWindow::logoutClicked, this, &MapWidget::closeAndShowLoginForm);
    }

    void closeAndShowLoginForm();

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);

        // Set background color to black
        painter.fillRect(this->rect(), Qt::gray);

        // Set pen for drawing lines (if needed)
        QPen linePen(Qt::white); // Set line color to black
        painter.setPen(linePen);

        // Generate 200 random points
        QVector<QPointF> points;
        for (int i = 0; i < 200; i++) {
            points.append(QPointF(rand() % 800, rand() % 800));
        }

        // Set brush for filling points
        QBrush pointBrush(Qt::red); // Set fill color to red
        painter.setBrush(pointBrush);

        // Draw solid circles with radius 2
        for (const QPointF &point : points) {
            painter.drawEllipse(point, 4, 4); // Set width and height to 2 for radius 2 circle
        }

        // Draw 500 random lines
        for (int i = 0; i < 500; i++) {
            int idx1 = rand() % points.size();
            int idx2 = rand() % points.size();
            painter.drawLine(points[idx1], points[idx2]);
        }
    }
};

void MapWidget::closeAndShowLoginForm() {
    // 关闭 MapWidget 窗口
    QMainWindow *mapWindow = qobject_cast<QMainWindow*>(parent());
    if (mapWindow) {
        mapWindow->close();
    }

    // 创建一个新的 LoginForm 窗口并显示
    LoginForm *loginForm = new LoginForm();
    loginForm->show();
}

//#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LoginForm loginForm;
    loginForm.show();

    return app.exec();
}
