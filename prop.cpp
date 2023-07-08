#include<prop.h>

Prop::Prop(QObject *parent,int type):
    QObject(parent), QGraphicsItem(),type(type){
    /*
     type:
            0. speed
            1. healing
            2. virtualable
            3. breakwall
    */
}
Prop::~Prop(){}

QRectF Prop::boundingRect() const{
    return QRectF(0, 0, 25, 25);
}

void Prop::slot_get_tank_posotion(qreal px,qreal py){
    if(abs(this->x() - px + 10) < 40 && abs(this->y() - py + 10) < 40){
        emit signal_send_position(this->x(),this->y(),type);
        this -> deleteLater();
    }
}

void Prop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QImage prop_speed(":/textures/images/speed.jpg");
    QImage prop_heal(":/textures/images/healing.jpg");
    QImage prop_virtual(":/textures/images/virtualable.jpg");
    QImage prop_breakwall(":/textures/images/breakwall.jpg");
    if (type == 0){
        painter->drawImage(QRectF(0, 0, 26, 26), prop_speed);
    }else if (type == 1){
        painter->drawImage(QRectF(0, 0, 26, 26), prop_heal);
    }else if (type == 2){
        painter->drawImage(QRectF(0, 0, 26, 26), prop_virtual);
    }else{
        painter->drawImage(QRectF(0, 0, 26, 26), prop_breakwall);
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
