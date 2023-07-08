#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QImage>
#include <QFile>
#include <QPixmap>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>

class Wall : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Wall(QObject *parent = 0,bool is_breakable = false,bool is_colorable = false,bool is_yellow = false);
    ~Wall();
    //bool is_box = 0;
    bool is_breakable = 0;
    bool is_colorable = 0;
    bool is_yellow = 0;

private:
    QTimer* timer;
signals:
    void signal_back_position(qreal x,qreal y);
public slots:
    void slot_destoryer(qreal px,qreal py);
    void slot_get_tank_position(qreal px,qreal py);
    void slot_get_tank_collision(QGraphicsItem* pitem);
    void slot_get_timeout();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // WALL_H
