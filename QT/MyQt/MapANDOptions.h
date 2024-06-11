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
void DrawPoints(void);

namespace Ui {
class MapANDOptions;
}


class Map_ : public QGraphicsView
{
    Q_OBJECT
public:
    Map_(QWidget *parent);
    void wheelEvent(QWheelEvent* event);
    ~Map_(){}
};

class MapANDOptions : public QWidget
{
    Q_OBJECT

public:
    MapANDOptions(QWidget *parent = nullptr);
    ~MapANDOptions();

private slots:


private:
    Ui::MapANDOptions *ui;
    Map_ *M;
};



#endif // MAPANDOPTIONS_H
