#include "MapANDOptions.h"
#include "GetPoints.h"
//#pragma execution_character_set("utf-8")  //防乱码

//(957,2064)  116.22300999999993  39.906590000000016
//(1407,1644)  116.2983200000001   39.959928000000026


Map_::Map_(QWidget *parent)
    : QGraphicsView(parent)
{
    //this->setStyleSheet("QToolTip { border:1px solid rgb(118, 118, 118); background-color: rgba(18, 26, 40,0.7); color:rgb(255, 255, 255); font:12px; }");
    readPoints();
    QGraphicsScene *Scene = new QGraphicsScene;
    QPixmap pixmap("D:\\MyCode\\DataStructure Project\\QT\\MyQt\\map.jpg");
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
        double X = (point[i].Longitude - 116) * 5975.3020847 - 375.5521179;
        double Y = (point[i].Latitude - 39) * (-7874.3109978) + 9202.7716075;
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
        Scene->addItem(proxy[i]);
    }
    QPen outlinePen(Qt::white); // Outer white pen for outline
    outlinePen.setWidth(2);
    QPen innerPen(Qt::black); // Inner black pen for the line
    innerPen.setWidth(1);
    QLineF line(proxy[1]->pos() , proxy[2]->pos());
    Scene->addLine(line,outlinePen);
    Scene->addLine(line,innerPen);
    this->setDragMode(QGraphicsView::ScrollHandDrag);   // Enable drag mode
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


}

MapANDOptions::~MapANDOptions()
{
    delete ui;
}

