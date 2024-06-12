#include "diaryall.h"
#include "ui_diaryall.h"
#include"uploadDiary.h"
#include"diaryDetail.h"

diaryAll::diaryAll(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::diaryAll)
{
    ui->setupUi(this);
    getAllDiary();
    showDiaryAll();
    layout = new QVBoxLayout(this);
    createDiaryEntries();
    setLayout(layout);
    setWindowTitle("日志浏览器");
    layout->setContentsMargins(20, 80, 20, 0);
}

QVector<diaryInfo> diaryAll::getAllDiary() {
    // 执行查询
    QSqlQuery query("SELECT * FROM diary", db);

    while (query.next()) {
        diaryInfo info;
        info.diaryId=query.value("diaryId").toInt();
        info.userId = query.value("userId").toInt();
        info.title = query.value("title").toString();
        info.destination = query.value("destination").toString();
        QByteArray uncompressedContent = qUncompress(query.value("content").toByteArray());
        info.content = QString::fromUtf8(uncompressedContent);
        info.exchangeCode = query.value("exchangeCode").toString();
        info.point=query.value("point").toFloat();
        info.browse = query.value("browse").toInt();
        info.time = query.value("time").toDateTime();
        diaryInfoList.append(info);
    }
    std::reverse(diaryInfoList.begin(), diaryInfoList.end());
    return diaryInfoList;
}

int diaryAll::showDiaryAll(){
    diaryInfoListShow = diaryInfoList;
    return diaryInfoListShow.size();
}

int diaryAll::showPopularityDiaryAll(){
    diaryInfoListShow = diaryInfoList;
    int n = diaryInfoListShow.size();
    int sortRange = std::min(10, n); // 确保排序范围不超过数组大小

    for (int i = 0; i < sortRange - 1; ++i) {
        for (int j = 0; j < sortRange - i - 1; ++j) {
            if (diaryInfoListShow[j].point < diaryInfoListShow[j + 1].point) {
                // 交换两个元素的位置
                std::swap(diaryInfoListShow[j], diaryInfoListShow[j + 1]);
            }
        }
    }
    return diaryInfoListShow.size();
}
int diaryAll::showBrowseDiaryAll(){
    diaryInfoListShow = diaryInfoList;
    int n = diaryInfoListShow.size();
    int sortRange = std::min(10, n); // 确保排序范围不超过数组大小

    for (int i = 0; i < sortRange - 1; ++i) {
        for (int j = 0; j < sortRange - i - 1; ++j) {
            if (diaryInfoListShow[j].browse < diaryInfoListShow[j + 1].browse) {
                // 交换两个元素的位置
                std::swap(diaryInfoListShow[j], diaryInfoListShow[j + 1]);
            }
        }
    }
    return diaryInfoListShow.size();
}

void diaryAll::createDiaryEntries() {
    for (const diaryInfo &log : diaryInfoListShow) {
        QLabel *titleLabel = new QLabel(log.title, this);
        QLabel *contentLabel = new QLabel(log.content.left(50) + "...", this);
        QPushButton *button = new QPushButton("查看详情", this);
        button->setProperty("diaryId", log.diaryId); // 设置按钮的自定义属性，用于标识对应的日志ID
        button->setProperty("userId", log.userId); // 设置按钮的自定义属性，用于标识对应的作者ID

        layout->addWidget(titleLabel);

        layout->addWidget(contentLabel);
        layout->addWidget(button);
        horizontalLayout = new QHBoxLayout;
        horizontalLayout->addWidget(contentLabel);
        // 创建一个弹性空间，将按钮推到最右侧
        QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout->addItem(spacer);

        // 设置按钮的固定大小
        button->setFixedSize(100, 30); // 例如宽度100，高度30
        horizontalLayout->addWidget(button);

        // 将水平布局添加到主垂直布局中
        layout->addLayout(horizontalLayout);
        // 创建分隔线
        QFrame *line = new QFrame(this);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setFixedHeight(1); // 设置线的高度，这里设置为2像素高
        line->setStyleSheet("background-color: black;"); // 设置线的颜色

        // 设置线的宽度为布局宽度的80%
        QHBoxLayout *lineLayout = new QHBoxLayout;
        // QSpacerItem *leftSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        // QSpacerItem *rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        // lineLayout->addItem(leftSpacer);
        lineLayout->addWidget(line);
        // lineLayout->addItem(rightSpacer);

        // 添加线的布局到主布局
        layout->addLayout(lineLayout);

        titleLabels.append(titleLabel);
        contentLabels.append(contentLabel);
        buttons.append(button);
        lines.append(line);

        connect(button, &QPushButton::clicked, this, &diaryAll::showDiaryDetail);
    }
}
void diaryAll::updateAllDiaryEntries() {
    int n = qMin(diaryInfoListShow.size(), titleLabels.size()); // 获取原始布局和数据列表中较小的长度

    for (int i = 0; i < n; ++i) {
        QLabel *titleLabel = titleLabels[i];
        QLabel *contentLabel = contentLabels[i];
        QPushButton *button = buttons[i];
        QFrame *line = lines[i];

        const diaryInfo &log = diaryInfoListShow[i]; // 获取当前日志信息

        // 更新titleLabel、contentLabel和button的属性
        titleLabel->setText(log.title);
        contentLabel->setText(log.content.left(50) + "...");
        button->setProperty("diaryId", log.diaryId);
        button->setProperty("userId", log.userId);

        // 显示控件
        titleLabel->setVisible(true);
        contentLabel->setVisible(true);
        button->setVisible(true);
        line->setVisible(true); // 显示分隔线
        button->setVisible(true);
        line->setVisible(true); // 隐藏分隔线
    }

    // 隐藏多余的控件
    for (int i = n; i < titleLabels.size(); ++i) {
        QLabel *titleLabel = titleLabels[i];
        QLabel *contentLabel = contentLabels[i];
        QPushButton *button = buttons[i];
        QFrame *line = lines[i];

        titleLabel->setText("");
        contentLabel->setText("");
        button->setVisible(false);
        line->setVisible(false); // 隐藏分隔线
    }
}
void diaryAll::updateDiaryEntries(){
    int i=0;
    int n=diaryInfoListShow.size();
    int sortRange = std::min(10, n); // 确保排序范围不超过数组大小
    for (i = 0; i < sortRange; ++i) {
        QLabel* titleLabel = titleLabels[i];
        QLabel* contentLabel = contentLabels[i];
        QPushButton* button = buttons[i];

        // 更新 titleLabel、contentLabel 和 button 的属性
        titleLabel->setText(diaryInfoListShow[i].title);
        contentLabel->setText(diaryInfoListShow[i].content);
        button->setProperty("diaryId", diaryInfoListShow[i].diaryId);
        button->setProperty("userId", diaryInfoListShow[i].userId);
    }
    for(i;i<diaryInfoListShow.size();i++){
        QLabel* titleLabel = titleLabels[i];
        QLabel* contentLabel = contentLabels[i];
        QPushButton* button = buttons[i];
        QFrame* line=lines[i];
        // 更新 titleLabel、contentLabel 和 button 的属性
        titleLabel->setText("");
        contentLabel->setText("");
        button->hide();
        line->setVisible(false); // 显示分隔线
    }
}
void diaryAll::showDiaryDetail() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int diaryId = button->property("diaryId").toInt();
        // 创建 SQL 查询对象
        QSqlQuery query;

        // 准备 SQL 更新语句
        query.prepare("UPDATE diary SET browse = browse + 1 WHERE diaryId = :diaryId");
        query.bindValue(":diaryId", diaryId);
        // 执行 SQL 更新语句
        if (!query.exec()) {
            QMessageBox::critical(this, "数据库错误", query.lastError().text());
            return;
        }
        // 成功更新，显示信息
        // QMessageBox::information(this, "日志详情", "这是日志 " + QString::number(diaryId) + " 的完整信息。浏览次数已增加。");
        diaryDetail *detailDiary = new diaryDetail(diaryId, this);
        detailDiary->exec();
    }
}
bool diaryAll::customContains(const QString &str, const QString &subStr) {
    int strLen = str.length();
    int subStrLen = subStr.length();

    for (int i = 0; i <= strLen - subStrLen; ++i) {
        int j;
        for (j = 0; j < subStrLen; ++j) {
            if (str[i + j] != subStr[j]) {
                break;
            }
        }
        if (j == subStrLen) {
            return true; // 找到匹配的子串
        }
    }
    return false; // 没有找到匹配的子串
}
int diaryAll::searchDiary(const QString &searchInput) {
    QVector<diaryInfo> tempDiaryInfoList;

    for (const auto &diary : diaryInfoList) {
        if (customContains(diary.title, searchInput) ||
            customContains(diary.content, searchInput)) {
            tempDiaryInfoList.append(diary);
        }
    }

    if (tempDiaryInfoList.isEmpty()) {
        diaryInfoListShow.clear();
        return 0;
    } else {
        diaryInfoListShow = tempDiaryInfoList;
        return 1;
    }
}

diaryAll::~diaryAll()
{
    delete ui;
}



// ---------------------------------------------------------------------------------------------------------------------

void diaryAll::on_allPushButton_clicked()
{
    if(page!=0){
        page=0;
        showDiaryAll();
        updateAllDiaryEntries();
        setLayout(layout);
    }

}


void diaryAll::on_uploadPushButton_clicked()
{
    uploadDiary *upload = new uploadDiary;
    upload->show();
}


void diaryAll::on_popularityPushButton_clicked()
{
    if(page!=1){
        page=1;
        showPopularityDiaryAll();
        updateDiaryEntries();
        setLayout(layout);
    }
}


void diaryAll::on_browsePushButton_clicked()
{
    if(page!=2){
        page=2;
        showBrowseDiaryAll();
        updateDiaryEntries();
        setLayout(layout);
    }
}


void diaryAll::on_searchPushButton_clicked()
{
    page=4;
    QString searchInput=ui->searchLineEdit->text();
    if(searchInput==""){
        QMessageBox::information(this, "search", "搜索内容不可为空");
    }
    else{
        int searchReturn=searchDiary(searchInput);
        for(int i=0;i<diaryInfoListShow.length();i++){
            qDebug()<<diaryInfoListShow[i].diaryId;
        }
        if(searchReturn==1){
            updateAllDiaryEntries();
            setLayout(layout);
        }
        else{
            QMessageBox::information(this, "search", "无此日记");
            ui->searchLineEdit->clear();
            updateAllDiaryEntries();
            setLayout(layout);
        }
    }

}

