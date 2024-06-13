#ifndef BUPT_H
#define BUPT_H
#include "ui_bupt.h"
#include "MapANDOptions.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <set>
#include <map>
#include <QRegularExpression>
namespace Ui {
class bupt;
}

/**/
class Map_bupt : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Map_bupt(QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void mousePositionChanged(double x, double y);

private slots:
    void updateMousePosition(double x, double y);

protected:
    QLabel *mousePositionLabel;
    ~Map_bupt() {}
};

/**************/


class bupt : public QWidget
{
    Q_OBJECT

public:
    bupt(QWidget *parent = nullptr);

    ~bupt();
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

    QPushButton *searchButton;
    QPushButton *foodButton;
    QPushButton *marksButton;
    QPushButton *viewsButton;
    QLineEdit *searchLineEdit;
    QListView *listView_Search;
    QListView *listView_food;
    QListView *listView_marks;
    QListView *listView_viwes;

    Ui::bupt *ui;

    Map_bupt *M;
};

void sortByTypeAndAddToModel(int select, QStandardItemModel *model , QString type);
QStringList parseCSVLine(const QString &line);
#endif // BUPT_H
