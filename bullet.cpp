
#include "Bullet.h"

Bullet::Bullet(QPointF start, int direction,tank* _target, QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    target=_target;
    setPos(start);
    setRotation(90*direction);

    timerBullet = new QTimer();
    timerBullet->start(1000/50);
    connect(timerBullet,&QTimer::timeout,this,&Bullet::slotMoveBullet);
}

Bullet::~Bullet(){}

void Bullet::slotMoveBullet(){
    if(!scene()->collidingItems(this).isEmpty()){
        if(!scene()->collidingItems(this).contains(target) && !scene()->collidingItems(this).contains(target->target)) {
            emit signal_send_position(this -> x(),this -> y());
            this->deleteLater();}
    }
    setPos(mapToParent(0, 5));

    // borders check，在全屏的时候没问题
    if(this->x() < -(width / 2)){
        this->deleteLater();       //left
    }
    if(this->x() > (width / 2)){
        this->deleteLater();
    }

    if(this->y()< -(height / 2)){
        this->deleteLater();       //up
    }
    if(this->y()> (height / 2)){
        this->deleteLater();        //down
    }

    if(abs(target->x()-this->x())<40 && abs(target->y()-this->y())<40){
        if (hitted){return;}
        hitted = true;
        emit signalhit(target);
        this -> deleteLater();
    }
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0,0,2,4);
}

void Bullet::slot_check_wall(qreal px,qreal py){
    if (abs(this -> x() - px + 20) < 25 && abs(this->y() - py + 20) < 25){
        qDebug("check wall called!");
        this -> deleteLater();
    }
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawRect(0,0,2,4);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}


