<<<<<<< HEAD
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QLineF>
#include <qline.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

// refer to widget.cpp for functions description
private:
    Ui::Widget *ui;
    void drawLines(QPainter *paint);
    QPoint firstPoint;
    QPoint lastPoint;
    bool secClick;
    bool stopDraw;
    QVector<QLineF> lines;
    void paintEvent(QPaintEvent *painter) ;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};


#endif // WIDGET_H
=======
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QLineF>
#include <qline.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

// refer to widget.cpp for functions description
private:
    Ui::Widget *ui;
    void drawLines(QPainter *paint);
    QPoint firstPoint;
    QPoint lastPoint;
    bool secClick;
    bool stopDraw;
    QVector<QLineF> lines;
    void paintEvent(QPaintEvent *painter) ;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};


#endif // WIDGET_H
>>>>>>> de12579657b7bdbeb610e853fb0ef5d3f56a3699
