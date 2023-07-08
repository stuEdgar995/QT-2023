#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsScene>

#include "tank.h"
#include "Wall.h"
#include "windows.h"


class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT;
public:
    explicit Bullet(QPointF start, int direction,tank* _target, QObject *parent = 0);
    ~Bullet();
signals:
    void signalhit(tank* target);   //bullet移动时碰到target就发出信号
    void signal_send_position(qreal px,qreal py);
public slots:
    void slot_check_wall(qreal px,qreal py);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QTimer *timerBullet; //实现子弹实时移动
    int direction;
    tank *target;
    int width = QGuiApplication::screens().at(0)->availableGeometry().width();
    int height = QGuiApplication::screens().at(0)->availableGeometry().height();
    bool hitted = false;

private slots:
    void slotMoveBullet();

};

#endif // BULLET_H

