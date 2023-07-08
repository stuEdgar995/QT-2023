
#ifndef PROP_H
#define PROP_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsScene>

#include <windows.h>

class Prop: public QObject, public QGraphicsItem{
    Q_OBJECT;
public:
    explicit Prop(QObject *parent = 0,int type = 0);
    ~Prop();
    int type;
public slots:
    void slot_get_tank_posotion(qreal px,qreal py);

signals:
    void signal_send_position(qreal px,qreal py,int type);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

};




#endif // PROP_H
