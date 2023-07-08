
#ifndef SKILL_H
#define SKILL_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsScene>

#include <windows.h>

class skill: public QObject, public QGraphicsItem{
    Q_OBJECT;
public:
    explicit skill(QObject *parent = 0,int type = 0);
    ~skill();
    int type;
    void update(bool visible);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
};

#endif // SKILL_H
