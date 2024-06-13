#include "bupt.h"
Map_bupt::Map_bupt(QWidget *parent)
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
    proxy_->setPos(1000.5,1000.5);


    this->setDragMode(QGraphicsView::ScrollHandDrag);
    //setMouseTracking(true);
    mousePositionLabel = new QLabel("Mouse Position: (0, 0)", this);
    mousePositionLabel->setAlignment(Qt::AlignCenter);
    mousePositionLabel->setFixedSize(500,20);
    connect(this, &Map_bupt::mousePositionChanged, this, &Map_bupt::updateMousePosition);
    readPoints();


    int bupt_index = nameToInedx_Mot[("北京邮电大学(海淀校区)")];
    qDebug() << bupt_index;

    QGraphicsScene *Scene = new QGraphicsScene;
    QPixmap pixmap("./point/bupt.jpg");
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pixmap);
    pixmapItem->setPos(500,500);
    pixmapItem->setScale(0.8);
    Scene->addItem(pixmapItem);
    Scene->setBackgroundBrush(Qt::white);
    Scene->setSceneRect(0, 0, 3600, 3600);
    QPushButton *Botton[nPoints];
    QGraphicsProxyWidget *proxy[nPoints];

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

        point[bupt_index].subPointsNum = j;
    }


    for (int i = 1;i <= point[bupt_index].subPointsNum;i++)
    {

        double X = point[bupt_index].subpoint[i].Longitude;
        double Y = point[bupt_index].subpoint[i].Latitude;
        Botton[i] = new QPushButton();
        Botton[i]->setToolTip(point[i].Name);
        Botton[i]->setObjectName("place");
        Botton[i]->setFixedSize(10,10);
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
