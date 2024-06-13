#ifndef MAPANDOPTIONS_H
#define MAPANDOPTIONS_H
#include "ui_MapANDOptions.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QWheelEvent>
#include <QScrollBar>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QListView>
#include <QStandardItemModel>
#include "GetPoints.h"
#include "MySQL_Operate.h"
#include <QLineEdit>
void DrawPoints(void);

namespace Ui {
class MapANDOptions;
}



/**/
class Map_ : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Map_(QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void mousePositionChanged(double x, double y);

private slots:
    void updateMousePosition(double x, double y);

protected:
    QLabel *mousePositionLabel;
    ~Map_() {}
};

/**************/


class MapANDOptions : public QWidget
{
    Q_OBJECT

public:
    MapANDOptions(QWidget *parent = nullptr);

    ~MapANDOptions();
    QStandardItemModel *model_search;
    QStandardItemModel *model_food;
    QStandardItemModel *model_marks;
    QStandardItemModel *model_views;


private slots:
    void filterChanged(const QString &text);
    void toggleSearch();
    void togglefood();
    void togglemarks();
    void toggleviews();

private:
    Ui::MapANDOptions *ui;
    QPushButton *searchButton;
    QPushButton *foodButton;
    QPushButton *marksButton;
    QPushButton *viewsButton;
    QLineEdit *searchLineEdit;
    QListView *listView_Search;
    QListView *listView_food;
    QListView *listView_marks;
    QListView *listView_viwes;


    std::vector<Point> points;
    Map_ *M;
};

void sortByTypeAndAddToModel(int select, QStandardItemModel *model , QString type);
#endif // MAPANDOPTIONS_H
