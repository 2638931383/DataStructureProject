#include "MapWidget.h"

void MapWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    // Generate 200 random points
    QVector<QPointF> points;
    for (int i = 0; i < 200; i++) {
        points.append(QPointF(rand() % 800, rand() % 800));
    }

    // Draw 500 random lines
    for (int i = 0; i < 500; i++) {
        int idx1 = rand() % points.size();
        int idx2 = rand() % points.size();
        painter.drawLine(points[idx1], points[idx2]);
    }
}
