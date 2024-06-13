#include "bupt.h"
Map_bupt::Map_bupt(QWidget *parent)
    : QGraphicsView(parent)
{




    this->setDragMode(QGraphicsView::ScrollHandDrag);
    //setMouseTracking(true);
    mousePositionLabel = new QLabel("Mouse Position: (0, 0)", this);
    mousePositionLabel->setAlignment(Qt::AlignCenter);
    mousePositionLabel->setFixedSize(500,20);
    connect(this, &Map_bupt::mousePositionChanged, this, &Map_bupt::updateMousePosition);
    readPoints();


    int bupt_index = nameToInedx_Mot[("北京邮电大学(海淀校区)")];
    //qDebug() << bupt_index;

    QGraphicsScene *Scene = new QGraphicsScene;
    QPixmap pixmap("./point/bupt.jpg");
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pixmap);
    pixmapItem->setPos(500,500);
    pixmapItem->setScale(0.8);
    Scene->addItem(pixmapItem);
    Scene->setBackgroundBrush(Qt::white);
    Scene->setSceneRect(0, 0, 3600, 3600);
    QPushButton *Botton[200];
    QGraphicsProxyWidget *proxy[200];

    QFile file("./point/北京邮电大学(海淀校区).csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << point[bupt_index].Name << "没有子点";
    }
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::System);
    /*************************************/


    /*************************************/
    int j = 0;
    while (!stream.atEnd()) {
        j++;
        QString line = stream.readLine();
        QStringList row = parseCSVLine(line);

        // Ensure there are at least 5 columns in the row
        if (row.size() < 5) {
            qDebug() << "Invalid row, skipping:" << line;
            continue;
        }

        // Convert and validate longitude and latitude
        bool ok;
        double lo = row[1].toDouble(&ok);
        if (!ok) {
            qDebug() << "Invalid longitude value in row:" << line;
            continue;
        }

        double la = row[2].toDouble(&ok);
        if (!ok) {
            qDebug() << "Invalid latitude value in row:" << line;
            continue;
        }

        QString name = row[0].trimmed();
        QString type = row[3].trimmed();
        QString padj = row[4].trimmed();
        QStringList pointsList = padj.split(',', Qt::SkipEmptyParts);

        // Parse adjacent points
        std::set<int> pointsadj;
        for (const QString &point_ : pointsList) {
            int pointInt = point_.toInt(&ok);
            if (ok) {
                pointsadj.insert(pointInt);
            } else {
                qDebug() << "Invalid adjacent point value in row:" << point_ << "from line:" << line;
            }
        }

        // Store the subpoint information
        point[bupt_index].subpoint[j] = subPoint(lo, name, la, 0, pointsadj, type);
        point[bupt_index].nameToInedxSub.insert(name, j);
        qDebug() << "Subpoint added:" << name << pointsList;
    }


    for (int i = 1;i <= j;i++)
    {

        double X = point[bupt_index].subpoint[i].Longitude;
        double Y = point[bupt_index].subpoint[i].Latitude;
        Botton[i] = new QPushButton();
        //Botton[i]->setToolTip(point[i].Name);
        Botton[i]->setObjectName("place");
        Botton[i]->setFixedSize(5,5);
        Botton[i]->setStyleSheet("QPushButton {"
                                 "background-color: red;"    // Red background
                                 "border: none;"
                                 "color: white;"                 // White text
                                 "border-radius: 1.5;"          // Rounded corners (circle)
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: #45a049;"    // Darker green when hovered
                                 "}");
        proxy[i] = new QGraphicsProxyWidget();
        proxy[i]->setWidget(Botton[i]);
        proxy[i]->setPos(X,Y);
        //qDebug() << sceneX << sceneY;
        Scene->addItem(proxy[i]);

    }

    //Scene->addItem(proxy_);

    // QLineF *line[nPoints >> 1];
    // memset(visited,false,sizeof(visited));
    // QPen outlinePen(Qt::white); // Outer white pen for outline
    // outlinePen.setWidth(2);
    // QPen innerPen(Qt::black); // Inner black pen for the line
    // innerPen.setWidth(1);

    // for (int i = 1;i <= nPoints;i++)
    // {
    //     if (point[i].pointsAdjNum == 0) continue;
    //     for (auto it = point[i].pointsAdj.begin();it != point[i].pointsAdj.end();it++)
    //     {
    //         if (visited[*it]) continue;
    //         visited[*it] = true;
    //         QPointF startPoint = proxy[i]->pos();
    //         QPointF endPoint = proxy[*it] -> pos();
    //         line[i] = new QLineF (startPoint , endPoint);
    //         Scene->addLine(*line[i] , outlinePen);
    //         Scene->addLine(*line[i] , innerPen);
    //     }
    // }


    // Enable drag mode
    this->setScene(Scene);
}


void Map_bupt::wheelEvent(QWheelEvent* event)
{
    // 获取当前鼠标相对于view的位置;
    QPointF cursorPoint = event->position();
    // 获取当前鼠标相对于scene的位置;
    QPointF scenePos = this->mapToScene(QPoint(cursorPoint.x(), cursorPoint.y()));
    // 获取view的宽高;
    qreal viewWidth = this->viewport()->width();
    qreal viewHeight = this->viewport()->height();
    // 获取当前鼠标位置相当于view大小的横纵比例;
    qreal hScale = cursorPoint.x() / viewWidth;
    qreal vScale = cursorPoint.y() / viewHeight;
    // 当前放缩倍数;
    //qreal scaleFactor = this->transform().m11();
    QPoint wheelDeltaValue = event->angleDelta();
    // 向上滚动，放大;
    if (wheelDeltaValue.y() > 0)
        this->scale(1.2, 1.2);
    // 向下滚动，缩小;
    else
        this->scale(1.0 / 1.2, 1.0 / 1.2);
    // 将scene坐标转换为放大缩小后的坐标;
    QPointF viewPoint = this->transform().map(scenePos);
    // 通过滚动条控制view放大缩小后的展示scene的位置;
    this->horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
    this->verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));
}
void Map_bupt::mouseMoveEvent(QMouseEvent *event)
{
    double x = event->pos().x();
    double y = event->pos().y();
    QPointF scenePos = mapToScene(QPoint(x, y));
    double sceneX = scenePos.x();
    double sceneY = scenePos.y();

    double X = ((x + 696356.298175) / 5999.742029);
    double Y = (326865.447942 - y) / 8139.050435;
    emit mousePositionChanged(sceneX, sceneY);
}

void Map_bupt::updateMousePosition(double x, double y)
{

    if (mousePositionLabel) {
        mousePositionLabel->setText(QString("Mouse Position: (%1, %2)")
                                        .arg(QString::number(x, 'f', 6))
                                        .arg(QString::number(y, 'f', 6)));
    }
}


bupt::bupt(QWidget *parent) :
    QWidget(parent),ui(new Ui::bupt),M(new Map_bupt(this))
{

    ui->setupUi(this);
    //ui->map->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->map->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    M->setObjectName("Map_");
    M->setGeometry(QRect(0, 0, 1000, 1000));


    QVBoxLayout *rightLayout = new QVBoxLayout();

    // 创建搜索按钮、搜索框和列表视图
    searchButton = new QPushButton("搜索", this);
    foodButton = new QPushButton("找附近", this);
    marksButton = new QPushButton("综合评价排名TOP20", this);
    viewsButton = new QPushButton("热度TOP20", this);
    searchLineEdit = new QLineEdit(this);
    listView_Search = new QListView(this);
    listView_food = new QListView(this);
    listView_marks = new QListView(this);
    listView_viwes = new QListView(this);
    model_search = new QStandardItemModel(this);
    model_views = new QStandardItemModel(this);
    model_food = new QStandardItemModel(this);
    model_marks = new QStandardItemModel(this);

    // 初始时隐藏搜索框和列表视图
    searchLineEdit->setVisible(false);
    listView_Search->setVisible(false);
    listView_food->setVisible(false);
    listView_marks->setVisible(false);
    listView_viwes->setVisible(false);

    // 添加搜索按钮、搜索框和列表视图到右侧布局中
    rightLayout->addWidget(searchButton);
    rightLayout->addWidget(searchLineEdit);
    rightLayout->addWidget(listView_Search);
    rightLayout->addWidget(foodButton);
    rightLayout->addWidget(listView_food);
    rightLayout->addWidget(marksButton);
    rightLayout->addWidget(listView_marks);
    rightLayout->addWidget(viewsButton);
    rightLayout->addWidget(listView_viwes);
    int select = 20;

    for (const auto &point : point) {
        QStandardItem *item = new QStandardItem(point.Name);
        item->setData(QVariant::fromValue(point), Qt::UserRole + 1);
        model_search->appendRow(item);
    }
    listView_Search->setModel(model_search);


    std::partial_sort(point, point + select, point + nPoints,
                      [](const Point &a, const Point &b) {
                          return a.marks >= b.marks; // 按照评分降序排序
                      });

    int i = 1;

    for (const auto &point : point) {
        if (i == select) break;
        QStandardItem *item = new QStandardItem(point.Name);
        item->setData(QVariant::fromValue(point), Qt::UserRole + 1);
        model_marks->appendRow(item);
        i++;
    }
    listView_marks->setModel(model_marks);

    std::partial_sort(point, point + select, point + nPoints,
                      [](const Point &a, const Point &b) {
                          return a.views >= b.views; // 按照评分降序排序
                      });

    int j = 1;

    for (const auto &point : point) {
        if (j == select) break;
        QStandardItem *item = new QStandardItem(point.Name);
        item->setData(QVariant::fromValue(point), Qt::UserRole + 1);
        model_views->appendRow(item);
        j++;
    }
    listView_viwes->setModel(model_marks);

    sortByTypeAndAddToModel(select, model_food , "餐饮");

    listView_food->setModel(model_food);


    connect(marksButton, &QPushButton::clicked, this, &bupt::togglemarks);
    connect(viewsButton, &QPushButton::clicked, this, &bupt::toggleviews);
    connect(searchLineEdit, &QLineEdit::textChanged, this, &bupt::filterChanged);
    connect(searchButton, &QPushButton::clicked, this, &bupt::toggleSearch);
    connect(foodButton, &QPushButton::clicked, this, &bupt::togglefood);

    QWidget *rightWidget = new QWidget(this);
    rightWidget->setFixedSize(200, 800);
    rightWidget->setLayout(rightLayout); // 将右侧布局设置到右侧widget上
    rightWidget->move(width() - rightWidget->width(), 0);

    // 将右侧widget添加到界面中
    rightWidget->show();



}

bupt::~bupt()
{
    delete ui;
}
QStringList parseCSVLine(const QString &line) {
    QStringList result;
    QString currentField;
    bool inQuotes = false;

    for (int i = 0; i < line.length(); ++i) {
        QChar c = line.at(i);

        if (c == '"') {
            if (inQuotes && i + 1 < line.length() && line.at(i + 1) == '"') {
                // Handle double quote "" inside quoted string
                currentField += c;
                ++i; // Skip the next quote
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            result.append(currentField.trimmed());
            currentField.clear();
        } else {
            currentField += c;
        }
    }

    if (!currentField.isEmpty()) {
        result.append(currentField.trimmed());
    }

    return result;
}


void bupt::filterChanged(const QString &text) {
    // 清空模型
    model_search->clear();

    // 使用输入的文本进行过滤
    for (const auto &point : point) {
        if (point.Name.contains(text, Qt::CaseInsensitive)) {
            QStandardItem *item = new QStandardItem(point.Name);
            item->setData(QVariant::fromValue(point), Qt::UserRole + 1);
            model_search->appendRow(item);
        }
    }
}

void bupt::toggleSearch() {
    bool isVisible = searchLineEdit->isVisible();
    searchLineEdit->setVisible(!isVisible);
    listView_Search->setVisible(!isVisible);
    searchButton->setText(!isVisible ? ("关闭搜索") : ("搜索"));
}

void bupt::togglefood() {
    bool isVisible1 = listView_food->isVisible();
    listView_food->setVisible(!isVisible1);
    foodButton->setText(!isVisible1 ? ("关闭美食推荐") : ("美食推荐TOP20"));
}

void bupt::togglemarks() {
    bool isVisible2 = listView_marks->isVisible();
    listView_marks->setVisible(!isVisible2);
    marksButton->setText(!isVisible2 ? ("关闭综合评价排名") : ("综合评价排名TOP20"));
}

void bupt::toggleviews() {
    bool isVisible3 = listView_viwes->isVisible();
    listView_viwes->setVisible(!isVisible3);
    viewsButton->setText(!isVisible3 ? ("关闭热榜") : ("热度TOP20"));
}
