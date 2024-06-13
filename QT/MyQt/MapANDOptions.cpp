#include "MapANDOptions.h"

//#pragma execution_character_set("utf-8")  //防乱码

//(2032.5,1856.79)  116.40298664204795  39.93301210408043
//(1459.85,1524.7)  116.30576089315718   39.985567960703165

//2481.156885 , 2050.488298         116.47791716554002, 39.90821315558428
//865.737218    1285.651734              116.20866897799934             40.00218438356832

Map_::Map_(QWidget *parent)
    : QGraphicsView(parent)
{

    QPushButton *A = new QPushButton();
    A->setObjectName("place");
    A->setFixedSize(100,100);
    A->setStyleSheet("QPushButton {"
                             "background-color: black;"    // Red background
                             "border: none;"
                             "color: white;"                 // White text
                             "border-radius: 1.5;"          // Rounded corners (circle)
                             "}"
                             "QPushButton:hover {"
                             "background-color: #45a049;"    // Darker green when hovered
                             "}");
    QGraphicsProxyWidget *proxy_ = new QGraphicsProxyWidget();
    proxy_->setWidget(A);
    proxy_->setPos(2000.5,2000.5);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    //setMouseTracking(true);
    mousePositionLabel = new QLabel("Mouse Position: (0, 0)", this);
    mousePositionLabel->setAlignment(Qt::AlignCenter);
    mousePositionLabel->setFixedSize(500,20);
    connect(this, &Map_::mousePositionChanged, this, &Map_::updateMousePosition);

    readPoints();

    QGraphicsScene *Scene = new QGraphicsScene;
    QPixmap pixmap("map.jpg");
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pixmap);
    pixmapItem->setPos(-300,-200);
    pixmapItem->setScale(0.8);
    Scene->addItem(pixmapItem);
    Scene->setBackgroundBrush(Qt::white);
    Scene->setSceneRect(0, 0, 3600, 3600);
    QPushButton *Botton[nPoints];
    QGraphicsProxyWidget *proxy[nPoints];
    for (int i = 1;i <= nPoints;i++)
    {

        double X = ((point[i].Longitude) * 5999.742029) - 696356.298175;
        double Y = ((point[i].Latitude) * (-8139.050435)) + 326865.447942;
        Botton[i] = new QPushButton();
        Botton[i]->setToolTip(point[i].Name);
        Botton[i]->setObjectName("place");
        Botton[i]->setFixedSize(3,3);
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

void Map_::wheelEvent(QWheelEvent* event)
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


MapANDOptions::MapANDOptions(QWidget *parent) :
    QWidget(parent),ui(new Ui::MapANDOptions),M(new Map_(this))
{

    ui->setupUi(this);
    //ui->map->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->map->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    M->setObjectName("Map_");
    M->setGeometry(QRect(0, 0, 1000, 1000));
    // 创建一个垂直布局，用于放置右侧的搜索组件

    QVBoxLayout *rightLayout = new QVBoxLayout();

    // 创建搜索按钮、搜索框和列表视图
    searchButton = new QPushButton("搜索", this);
    foodButton = new QPushButton("美食推荐TOP20", this);
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


    connect(marksButton, &QPushButton::clicked, this, &MapANDOptions::togglemarks);
    connect(viewsButton, &QPushButton::clicked, this, &MapANDOptions::toggleviews);
    connect(searchLineEdit, &QLineEdit::textChanged, this, &MapANDOptions::filterChanged);
    connect(searchButton, &QPushButton::clicked, this, &MapANDOptions::toggleSearch);
    connect(foodButton, &QPushButton::clicked, this, &MapANDOptions::togglefood);

    QWidget *rightWidget = new QWidget(this);
    rightWidget->setFixedSize(200, 800);
    rightWidget->setLayout(rightLayout); // 将右侧布局设置到右侧widget上
    rightWidget->move(width() - rightWidget->width(), 0);

    // 将右侧widget添加到界面中
    rightWidget->show();

}



void Map_::mouseMoveEvent(QMouseEvent *event)
{
    double x = event->pos().x();
    double y = event->pos().y();
    QPointF scenePos = mapToScene(QPoint(x, y));
    double sceneX = scenePos.x();
    double sceneY = scenePos.y();

    double X = ((x + 696356.298175) / 5999.742029);
    double Y = (326865.447942 - y) / 8139.050435;
    emit mousePositionChanged(X, Y);
}



MapANDOptions::~MapANDOptions()
{
    delete ui;
}

void Map_::updateMousePosition(double x, double y)
{

    if (mousePositionLabel) {
        mousePositionLabel->setText(QString("Mouse Position: (%1, %2)")
                                        .arg(QString::number(x, 'f', 6))
                                        .arg(QString::number(y, 'f', 6)));
    }
}


void MapANDOptions::filterChanged(const QString &text) {
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

void MapANDOptions::toggleSearch() {
    bool isVisible = searchLineEdit->isVisible();
    searchLineEdit->setVisible(!isVisible);
    listView_Search->setVisible(!isVisible);
    searchButton->setText(!isVisible ? ("关闭搜索") : ("搜索"));
}

void MapANDOptions::togglefood() {
    bool isVisible1 = listView_food->isVisible();
    listView_food->setVisible(!isVisible1);
    foodButton->setText(!isVisible1 ? ("关闭美食推荐") : ("美食推荐TOP20"));
}

void MapANDOptions::togglemarks() {
    bool isVisible2 = listView_marks->isVisible();
    listView_marks->setVisible(!isVisible2);
    marksButton->setText(!isVisible2 ? ("关闭综合评价排名") : ("综合评价排名TOP20"));
}

void MapANDOptions::toggleviews() {
    bool isVisible3 = listView_viwes->isVisible();
    listView_viwes->setVisible(!isVisible3);
    viewsButton->setText(!isVisible3 ? ("关闭热榜") : ("热度TOP20"));
}

void sortByTypeAndAddToModel(int select, QStandardItemModel *model , QString type)
{
    std::vector<Point> schoolPoints;

    for (int i = 1; i <= nPoints; ++i) {
        if((point[i].Type).compare(type) == 0) {
            schoolPoints.push_back(point[i]);
        }
    }

    int numSchoolPoints = schoolPoints.size();
    if (numSchoolPoints > 0) {
        std::partial_sort(schoolPoints.begin(), schoolPoints.begin() + std::min(select, numSchoolPoints), schoolPoints.end(),
                          [](const Point &a, const Point &b) {
                              return a.views >= b.views; // 按照评分降序排序
                          });

        // 将排序后的部分数据添加到模型中
        for (int i = 1; i < std::min(select, numSchoolPoints); ++i) {
            QStandardItem *item = new QStandardItem(schoolPoints[i].Name);
            item->setData(QVariant::fromValue(schoolPoints[i]), Qt::UserRole + 1);
            model->appendRow(item);
            qDebug() << schoolPoints[i].Name;
        }
    }
}

void MapANDOptions::on_pushButton_clicked()
{
    bupt * b = new bupt();
    b->show();
    this->close();
}

