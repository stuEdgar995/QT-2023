
#include "skill.h"

skill::skill(QObject *parent,int type):
    QObject(parent), QGraphicsItem(),type(type)
{
    /*
     type:
            0. disable shooting
    */
}
skill::~skill(){}

void skill::update(bool visible){
    setVisible(visible);
}

QRectF skill::boundingRect() const{
    return QRectF(0, 0, 50, 70);
}

void skill::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QImage skill_f(":/textures/images/protect.png");
    if (type == 0){
        painter->drawImage(QRectF(0, 0, 50, 70), skill_f);
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

