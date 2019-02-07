// FILE:          lineDraw.cpp
// TITLE:         Line w/o intersection
// SUBMITTED BY:  Masood Ahmed Rafay
//                All code is my own except where credited.
// FOR Job Test:  Leica Geosystems AB
// DUE DATE:      February 05, 2019
//
// PURPOSE:
// This program will take two points from the user as mouse click events
// and draw a line between those two points. Also, it will check whether
// the line drawn is intersecting any previous line. If new line intersects
// previous line, it will show an error message "line crossed" and upon
// the next click the intersecting line will disappear.
//
// OVERALL METHOD:
//    The list of general tasks is:
//    1. Take a start point from user as line's starting point.
//    2. Take an end point from user as line's ending point.
//    3. Trace the mouse movement upon first click until the second click.
//    4. Draw a line between those two points.
//    5. Check whether the line drwan intersects any previous line.
//    6. If a new line intersects any previous line, the line should not be drawn.
//
// FUNCTIONS:
//
// mousePressEvent
//    will read a button press event when user click left mouse button
//    checks bounded intersection of a line (i.e line crossed b/w points)
//    return first and last point of a line and pass message to the message
//    box if line intersects
//
// mouseMoveEvent
//    trace the movement of mouse b/w first and last point of the line
//
// drawLines
//    set the path of line between two points
//
// paintEvent
//    draw a line between points
//
// INCLUDED FILES:
//    lineDraw.h
//    ui_widget.h
//    QMessageBox
#include "lineDraw.h"
#include "ui_widget.h"
#include <QMessageBox>
//
// name OF FUNCTION: Widget
// CREDIT: Qt library
// PURPOSE:
//    Creating the user interface window for the application
//
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    // Global variables
    firstPoint = QPoint();
    lastPoint = QPoint();
    secClick = false;
    setMouseTracking(true);
}
// name OF FUNCTION: mousePressEvent
// CREDIT:
// PURPOSE:
//    This program will take two points from the user as mouse click events
// and draw a line between those two points. Also, it will check whether
// the line drawn is intersecting any previous line. If new line intersects
// previous line, it will show an error message "line crossed" and upon
// the next click the intersecting line will disappear.
//
// PARAMETERS:
// name         type  value/reference   description
// ---------------------------------------------------------------------
// firstPoint   int   value         x,y co-ordinates of the first point
// lastPoint    int   value         x,y co-ordinates of the second point
// secClick     bool  value         check whether the mouse clicked for
//                                  first point or last point
//
// RETURN VALUE:
// name         type  description
// ---------------------------------------------------------------------
// linecross    bool  check whether the line drawn does not intersect
//                    any previous line
//
// METHOD: The following is pseudocode describing how the function works.
// 1. Check if left mouse button pressed.
//    1.1 Check if the button pressed for first time
//        1.1.1 Gets the x,y co-ordinates of the position and save as
//              first point.
//    1.2 If the button pressed for second time
//        1.2.1 Gets the x,y co-ordinates of the position and save as
//              last point.
//        1.2.2 Check the line intersects any previous line.
//              1.2.2.3  Display error message "line crossed" if it
//                       intersects
//    2.1 Draw line if two points received and does not intersect with
//        previous line.
//    3.1 Reset the click event.
//
void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)//Check if left mouse button pressed.
    {
        if (!secClick)                  //Check if the button pressed for first time
        {
            firstPoint = event->pos();  // Gets the x,y co-ordinates of the position and save as
                                        // first point
        }
        else
        {
            lastPoint = event->pos();   // Gets the x,y co-ordinates of the position and save as
                                        // last point.

            QLineF line = QLineF(firstPoint, event->pos());

            QMessageBox Msgbox;         // init message window
            bool linecross = false;     // no line intersection

            if(lines.length() > 0){
                QPointF* pIntersectionPoint= new QPointF; // setting the floating points of the line

                for(int i=0; i< lines.length(); i++ ){
                    if (QLineF :: BoundedIntersection == lines[i].intersect(line,pIntersectionPoint)){
                        linecross= true;    // line intersects
                    }
                }
                if(linecross){
                    Msgbox.setText("Line crossed"); // passing the message to the message box
                    Msgbox.exec();  // runs the message window
                }
            }
            if(!linecross)
                lines.append(line); // create line
        }
        secClick = !secClick;   // reset the click event
    }
}
//
// name OF FUNCTION: mouseMoveEvent
// CREDIT:
// PURPOSE:
//    trace the movement of mouse b/w first and last point of the line
//
// PARAMETERS:
// name         type  value/reference   description
// ---------------------------------------------------------------------
// secClick     bool  reference         check mouse press event
//
// RETURN VALUE:
// name         type  description
// ---------------------------------------------------------------------
// lastPoint    int   Updates the x,y co-ordinates of the position and save as
//                    last point on second click.
//
// name OF FUNCTION: mouseMoveEvent
// CREDIT:
// PURPOSE:
//    trace the movement of mouse b/w first and last point of the line
//
// PARAMETERS:
// name         type  value/reference   description
// ---------------------------------------------------------------------
// secClick     bool  reference         check mouse press event
//
// RETURN VALUE:
// name         type  description
// ---------------------------------------------------------------------
// lastPoint    int   Updates the x,y co-ordinates of the position and save as
//                    last point on second click.
//
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (secClick)   //
    {
        lastPoint = event->pos();
        update();
    }
}
// name OF FUNCTION: drawLines
// CREDIT:
// PURPOSE:
//    set the path of line between two points
//
void Widget::drawLines(QPainter *paint)
{
    if (!firstPoint.isNull() && !lastPoint.isNull()) // check whether both points has some value
    {
        paint->drawLine(firstPoint, lastPoint);
    }
    paint->drawLines(lines);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPen pointpen(Qt::blue);    // set the color of points to blue
    pointpen.setWidth(4);       // set the width of points to 4pixel

    QPen linepen(Qt::black);    // set the color of points to black
    linepen.setWidth(2);        // set the width of points to 2pixel

    QPoint P1;
    P1 = firstPoint;            // assigning the co-ordinates of first point to P1

    QPoint P2;
    P2 = lastPoint;             // assigning the co-ordinates of first point to P1

    // Drawing the points
    painter.setPen(pointpen);
    painter.drawPoint(P1);
    painter.drawPoint(P2);

    // Drawing the line
    painter.setPen(linepen);
    drawLines(&painter);
}
//
// name OF FUNCTION: mouseMoveEvent
// CREDIT: Qt libraries
// PURPOSE:
//    Ends the user interface
Widget::~Widget()
{
    delete ui;
}
