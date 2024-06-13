#include "diaryall.h"
#include "ui_diaryall.h"
#include"uploadDiary.h"
#include"diaryDetail.h"
#include"mine.h"

diaryAll::diaryAll(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::diaryAll)
{
    ui->setupUi(this);
    ui->allPushButton->setStyleSheet(seletcedStyleSheet);
    ui->popularityPushButton->setStyleSheet(initialStyleSheet);
    ui->browsePushButton->setStyleSheet(initialStyleSheet);
    ui->refreshPushButton->setStyleSheet(initialStyleSheet);
    getAllDiary();
    diaryInfoListShow = diaryInfoList;
    showDiaryAll();
    layout = new QVBoxLayout(this);
    createDiaryEntries();
    // setLayout(layout);
    setLayout(mainLayout);
    setWindowTitle("日志浏览器");
    mainLayout->setContentsMargins(20, 80, 20, 0);
    // layout->setContentsMargins(20, 80, 20, 0);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &diaryAll::onSearchTextChanged);
    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addItem(verticalSpacer);
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    // 将 navigatorPushButton 添加到主布局中，放在 QSpacerItem 之后
    buttonLayout->addWidget(ui->navigatorButton);
    buttonLayout->addWidget(ui->recommendButton);
    buttonLayout->addWidget(ui->diaryButton);
    buttonLayout->addWidget(ui->mineButton);
    mainLayout->addLayout(buttonLayout);
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
    std::sort(diaryInfoListShow.begin(), diaryInfoListShow.end(), [](const diaryInfo &a, const diaryInfo &b) {
        return a.diaryId > b.diaryId;
    });
    return diaryInfoListShow.size();
}

int diaryAll::showPopularityDiaryAll(){

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
        QLabel *contentLabel = new QLabel(log.content.left(20) + "...", this);
        QLabel *timeLabel = new QLabel("日记时间:"+log.time.toString("yyyy年M月d日HH:mm"), this); // 使用toString方法将QDateTime转换为指定格式的字符串
        QLabel *pointLabel = new QLabel("评分:"+QString::number(log.point ,'f', 2), this); // 使用QString::number方法将int类型转换为QString
        QLabel *browseLabel = new QLabel("浏览量:"+QString::number(log.browse), this);
        QLabel *destinationLabel = new QLabel(log.destination, this);
        QPushButton *button = new QPushButton("查看详情", this);
        button->setProperty("diaryId", log.diaryId); // 设置按钮的自定义属性，用于标识对应的日志ID
        button->setProperty("userId", log.userId); // 设置按钮的自定义属性，用于标识对应的作者ID

        QHBoxLayout *headLayout = new QHBoxLayout;
        headLayout->addWidget(titleLabel);
        headLayout->addWidget(pointLabel);
        headLayout->addWidget(browseLabel);
        QHBoxLayout *midLayout = new QHBoxLayout;
        midLayout->addWidget(destinationLabel);
        QSpacerItem *spacer = new QSpacerItem(35, 20, QSizePolicy::Expanding, QSizePolicy::Minimum); // 添加一个弹性空间
        midLayout->addItem(spacer);
        midLayout->addWidget(timeLabel);
        // layout->addWidget(contentLabel);
        // layout->addWidget(button);
        QHBoxLayout *horizontalLayout = new QHBoxLayout;
        horizontalLayout->addWidget(contentLabel);
        // 创建一个弹性空间，将按钮推到最右侧
        QSpacerItem *spacer1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout->addItem(spacer1);

        // 设置按钮的固定大小
        button->setFixedSize(100, 30); // 例如宽度100，高度30
        horizontalLayout->addWidget(button);

        // 将水平布局添加到主垂直布局中
        layout->addLayout(headLayout);
        layout->addLayout(midLayout);
        layout->addLayout(horizontalLayout);

        // 创建分隔线
        QFrame *line = new QFrame(this);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setFixedHeight(1); // 设置线的高度，这里设置为2像素高
        line->setStyleSheet("background-color: black;"); // 设置线的颜色

        // 设置线的宽度为布局宽度的80%
        QHBoxLayout *lineLayout = new QHBoxLayout;
        lineLayout->addWidget(line);

        // 添加线的布局到主布局
        layout->addLayout(lineLayout);

        titleLabels.append(titleLabel);
        contentLabels.append(contentLabel);
        timeLabels.append(timeLabel);
        pointLabels.append(pointLabel);
        browseLabels.append(browseLabel);
        destinationLabels.append(destinationLabel);
        buttons.append(button);
        lines.append(line);

        connect(button, &QPushButton::clicked, this, &diaryAll::showDiaryDetail);

    }
    // 创建一个临时小部件，用来管理布局
    QWidget *containerWidget = new QWidget;
    containerWidget->setLayout(layout);

    // 创建QScrollArea并设置它的内容为containerWidget
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true);

    // 设置主布局
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(scrollArea);
}
void diaryAll::updateAllDiaryEntries() {
    int n = qMin(diaryInfoListShow.size(), titleLabels.size()); // 获取原始布局和数据列表中较小的长度

    for (int i = 0; i < n; ++i) {
        QLabel *titleLabel = titleLabels[i];
        QLabel *contentLabel = contentLabels[i];
        QPushButton *button = buttons[i];
        QLabel* timeLabel = timeLabels[i];
        QLabel* pointLabel = pointLabels[i];
        QLabel* destinationLabel = destinationLabels[i];
        QLabel* browseLabel = browseLabels[i];
        QFrame *line = lines[i];

        const diaryInfo &log = diaryInfoListShow[i]; // 获取当前日志信息

        // 更新titleLabel、contentLabel和button的属性
        titleLabel->setText(log.title);
        contentLabel->setText(log.content.left(20) + "...");
        button->setProperty("diaryId", log.diaryId);
        button->setProperty("userId", log.userId);
        timeLabel->setText("日记时间:"+diaryInfoListShow[i].time.toString("yyyy年M月d日HH:mm"));
        pointLabel->setText("评分:"+QString::number(diaryInfoListShow[i].point, 'f', 2));
        destinationLabel->setText(diaryInfoListShow[i].destination);
        browseLabel->setText("浏览量:"+QString::number(diaryInfoListShow[i].browse));
        // 显示控件
        titleLabel->setVisible(true);
        contentLabel->setVisible(true);
        timeLabel->setVisible(true);
        pointLabel->setVisible(true);
        destinationLabel->setVisible(true);
        browseLabel->setVisible(true);

        button->setVisible(true);
        line->setVisible(true); // 显示分隔线
    }

    // 隐藏多余的控件
    for (int i = n; i < qMax(diaryInfoListShow.size(), diaryInfoList.size()); ++i) {
        QLabel *titleLabel = titleLabels[i];
        QLabel *contentLabel = contentLabels[i];
        QPushButton *button = buttons[i];
        QLabel* timeLabel = timeLabels[i];
        QLabel* pointLabel = pointLabels[i];
        QLabel* destinationLabel = destinationLabels[i];
        QLabel* browseLabel = browseLabels[i];
        QFrame *line = lines[i];

        titleLabel->setText("");
        contentLabel->setText("");
        timeLabel->setText("");
        pointLabel->setText("");
        destinationLabel->setText("");
        browseLabel->setText("");
        button->setVisible(false);
        line->setVisible(false); // 隐藏分隔线
    }
}
void diaryAll::updateDiaryEntries(){
    int i=0;
    int n=diaryInfoListShow.size();
    int sortRange = qMin(10, n); // 确保排序范围不超过数组大小
    for (i = 0; i < sortRange; ++i) {
        QLabel* titleLabel = titleLabels[i];
        QLabel* contentLabel = contentLabels[i];
        QPushButton* button = buttons[i];
        QLabel* timeLabel = timeLabels[i];
        QLabel* pointLabel = pointLabels[i];
        QLabel* destinationLabel = destinationLabels[i];
        QLabel* browseLabel = browseLabels[i];
        QFrame* line=lines[i];
        // 更新 titleLabel、contentLabel 和 button 的属性
        titleLabel->setText(diaryInfoListShow[i].title);
        contentLabel->setText(diaryInfoListShow[i].content.left(20) + "...");
        timeLabel->setText("日记时间:"+diaryInfoListShow[i].time.toString("yyyy年M月d日HH:mm"));
        pointLabel->setText("评分:"+QString::number(diaryInfoListShow[i].point, 'f', 2));
        destinationLabel->setText(diaryInfoListShow[i].destination);
        browseLabel->setText("浏览量:"+QString::number(diaryInfoListShow[i].browse));
        button->setProperty("diaryId", diaryInfoListShow[i].diaryId);
        button->setProperty("userId", diaryInfoListShow[i].userId);
        button->setVisible(true);
        line->setVisible(true); // 显示分隔线
    }
    for(i;i<qMax(diaryInfoList.size(), n);++i){
        QLabel* titleLabel = titleLabels[i];
        QLabel* contentLabel = contentLabels[i];
        QPushButton* button = buttons[i];
        QLabel* timeLabel = timeLabels[i];
        QLabel* pointLabel = pointLabels[i];
        QLabel* destinationLabel = destinationLabels[i];
        QLabel* browseLabel = browseLabels[i];
        QFrame* line=lines[i];
        // 更新 titleLabel、contentLabel 和 button 的属性
        titleLabel->setText("");
        contentLabel->setText("");
        timeLabel->setText("");
        pointLabel->setText("");
        destinationLabel->setText("");
        browseLabel->setText("");
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
            customContains(diary.content, searchInput)|| customContains(diary.destination, searchInput)) {
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
void diaryAll::onSearchTextChanged(const QString &text) {
    searchInput = text;
    qDebug()<<searchInput;
    if(searchInput==""){
        isSearch=0;
    }
    else{
        isSearch=1;
    }
}
void diaryAll::refresh(){
    // isSearch=0;
    // searchInput="";
    // ui->searchLineEdit->setText("");
    // getAllDiary();
    // diaryInfoListShow = diaryInfoList;
    // switch(page){
    // case 0:
    //     showDiaryAll();
    //     updateAllDiaryEntries();
    //     setLayout(layout);
    //     break;
    // case 1:
    //     showPopularityDiaryAll();
    //     updateDiaryEntries();
    //     setLayout(layout);
    //     break;
    // case 2:
    //     showBrowseDiaryAll();
    //     updateDiaryEntries();
    //     setLayout(layout);
    //     break;
    // default:break;
    // }
    QMessageBox::information(this, "refresh", "刷新成功!");
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
        ui->allPushButton->setStyleSheet(seletcedStyleSheet);
        ui->popularityPushButton->setStyleSheet(initialStyleSheet);
        ui->browsePushButton->setStyleSheet(initialStyleSheet);
        ui->refreshPushButton->setStyleSheet(initialStyleSheet);
        if(isSearch==0){
            diaryInfoListShow = diaryInfoList;
        }
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
        ui->allPushButton->setStyleSheet(initialStyleSheet);
        ui->popularityPushButton->setStyleSheet(seletcedStyleSheet);
        ui->browsePushButton->setStyleSheet(initialStyleSheet);
        ui->refreshPushButton->setStyleSheet(initialStyleSheet);
        if(isSearch==0){
            diaryInfoListShow = diaryInfoList;
        }
        showPopularityDiaryAll();
        updateDiaryEntries();
        setLayout(layout);
    }
}


void diaryAll::on_browsePushButton_clicked()
{
    if(page!=2){
        page=2;
        ui->allPushButton->setStyleSheet(initialStyleSheet);
        ui->popularityPushButton->setStyleSheet(initialStyleSheet);
        ui->browsePushButton->setStyleSheet(seletcedStyleSheet);
        ui->refreshPushButton->setStyleSheet(initialStyleSheet);
        if(isSearch==0){
            diaryInfoListShow = diaryInfoList;
            showBrowseDiaryAll();
        }
        else{
            showBrowseDiaryAll();
        }
        updateDiaryEntries();
        setLayout(layout);
    }
}


void diaryAll::on_searchPushButton_clicked()
{

    if(searchInput==""){
        QMessageBox::information(this, "search", "搜索内容不可为空");
    }
    else{
        isSearch=1;
        int searchReturn=searchDiary(searchInput);
        for(int i=0;i<diaryInfoListShow.length();i++){
            qDebug()<<diaryInfoListShow[i].diaryId;
        }
        if(searchReturn==1){
            switch(page){
            case 0:
                showDiaryAll();
                updateAllDiaryEntries();
                setLayout(layout);
                break;
            case 1:
                showPopularityDiaryAll();
                updateDiaryEntries();
                setLayout(layout);
                break;
            case 2:
                showBrowseDiaryAll();
                updateDiaryEntries();
                setLayout(layout);
                break;
            default:
                updateDiaryEntries();
                setLayout(layout);
                break;
            }


        }
        else{
            QMessageBox::information(this, "search", "无此日记");
            ui->searchLineEdit->clear();
            updateAllDiaryEntries();
            setLayout(layout);
        }
    }

}



void diaryAll::on_refreshPushButton_clicked()
{
    refresh();
}


void diaryAll::on_mineButton_clicked()
{
    mine *user = new mine;
    QTimer::singleShot(1000, this, &QWidget::close); // 延迟关闭当前窗口
    user->show();
}

