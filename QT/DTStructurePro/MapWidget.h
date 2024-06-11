#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QMainWindow>
#include <QPaintEvent>

class MapWidget : public QWidget {

public:
    MapWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(800, 800);
    }
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MAPWIDGET_H
