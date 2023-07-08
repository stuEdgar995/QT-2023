#include "wall.h"

Wall::Wall(QObject *parent, bool is_breakable, bool is_colorable, bool is_yellow) :
    QObject(parent), QGraphicsItem(), is_breakable(is_breakable), is_colorable(is_colorable), is_yellow(is_yellow)
{
    if(is_colorable) {
        timer = new QTimer(this);
        timer->setSingleShot(true);
        connect(timer,QTimer::timeout,this,slot_get_timeout);
    }
}

Wall::~Wall()
{
}

QRectF Wall::boundingRect() const
{
    return QRectF(0, 0, 41, 41);   /// Ограничиваем область, в которой лежит треугольник
}

void Wall::slot_destoryer(qreal px,qreal py){
    if (!this -> is_breakable){return;}

    if (abs(this -> x() - px + 20) < 25 && abs(this->y() - py + 20) < 25){
        emit signal_back_position(this -> x(),this -> y());
        this -> deleteLater();
    }
}

void Wall::slot_get_tank_position(qreal px,qreal py){
    if(!is_colorable) {return;}
    if (abs(this -> x() - px) + abs(this->y() - py) < 180){
        if(is_yellow){return;}
        is_yellow = true;
        update();
    }else{
        if(!is_yellow){return;}
        is_yellow = false;
        update();
    }
}

void Wall::slot_get_tank_collision(QGraphicsItem* pitem){
    if(pitem!=this) return;
    if(!is_colorable) {return;}
    if(is_yellow){return;}
    is_yellow = true;
    timer->start(200);
    update();
}

void Wall::slot_get_timeout() {
    if(!is_colorable) {return;}
    is_yellow = false;
    update();
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QImage texture_image1(file_path + "/forest.jpg");
    //QString file_path = PRO_FILE_PWD;
    QImage texture_box(":/textures/images/box.jpg");
    QImage texture_brick(":/textures/images/bricks.png");

    //QImage texture_image;

    /*if(is_box) {
       texture_image = texture_image1;
    } else {
       texture_image = texture_image2;
    }*/
    if(is_colorable){
        if(!is_yellow){
            painter->setBrush(Qt::green);
        }else{
            painter->setBrush(Qt::yellow);
        }
        painter->drawRect(0, 0, 40, 40);
    }else if(is_breakable){
        painter->drawImage(QRectF(0, 0, 41, 41), texture_box);
    }else{
        painter->drawImage(QRectF(0, 0, 41, 41), texture_brick);}

        //painter->drawRect(0, 0, 50, 50);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
