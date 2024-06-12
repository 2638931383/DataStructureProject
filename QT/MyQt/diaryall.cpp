#include "diaryall.h"
#include "ui_diaryall.h"
#include"uploadDiary.h"

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
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (diaryInfoListShow[j].point < diaryInfoListShow[j + 1].point) {
                // 交换两个元素的位置
                std::swap(diaryInfoListShow[j], diaryInfoListShow[j + 1]);
            }
        }
    }
    return diaryInfoListShow.size();
}

void diaryAll::createDiaryEntries() {
    for (const diaryInfo &log : diaryInfoListShow) {
        titleLabel = new QLabel(log.title, this);
        contentLabel = new QLabel(log.content.left(50) + "...", this);
        button = new QPushButton("查看详情", this);
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
        connect(button, &QPushButton::clicked, this, &diaryAll::showDiaryAll);
    }
}
void diaryAll::updateDiaryEntries() {
    for (const diaryInfo &log : diaryInfoListShow) {
        button->setProperty("diaryId", log.diaryId); // 设置按钮的自定义属性，用于标识对应的日志ID
        button->setProperty("userId", log.userId); // 设置按钮的自定义属性，用于标识对应的作者ID
        titleLabel->setText(log.title);
        // 修改 contentLabel 的文本
        contentLabel->setText(log.content);
    }
}
void diaryAll::showDiaryDetail() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int diaryId = button->property("diaryId").toInt();

        // 在这里根据日志ID查找日志信息并显示
        // 假设 diaryAllList 是你的日志数组
        // 此处应该根据 diaryId 找到对应的日志，并显示完整的日志信息
        QMessageBox::information(this, "日志详情", "这是日志 " + QString::number(diaryId) + " 的完整信息。");
    }
}
diaryAll::~diaryAll()
{
    delete ui;
}

void diaryAll::on_allPushButton_clicked()
{
    if(page!=0){
        page=0;
        showDiaryAll();
        updateDiaryEntries();
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

