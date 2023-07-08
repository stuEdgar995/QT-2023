#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include "wall.h"
#include "tank.h"
#include "bullet.h"
#include "utils.h"
#include "skill.h"
#include <QSize>
#include <QWidget>

#include <string>


class MainScene : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MainScene(QWidget *parent = 0,Config* config = nullptr);
    int w = QGuiApplication::screens().at(0)->availableGeometry().width();
    int h = QGuiApplication::screens().at(0)->availableGeometry().height();
public slots:
    void slot_get_bullet_position(qreal px,qreal py);
    void slot_get_wall_position(qreal px,qreal py);
    void slot_get_tank_position(qreal px,qreal py);
    void slot_get_tank_collision(QGraphicsItem* pitem);
    void slot_get_prop_posotion(qreal px,qreal py,int type);
    void slot_make_prop();
signals:
    //void signalDamage(int);
    void signalConnect(int health,int id);
    void signal_bullet_position(qreal px,qreal py);
    void signal_wall_positon(qreal px,qreal py);
    void signal_tank_position(qreal px,qreal py);
    void signal_tank_collision(QGraphicsItem* pitem);
    void signal_prop_position(qreal px,qreal py,int type);
private:

static QList<QGraphicsItem *> target_tank1;//target list
static QList<QGraphicsItem *> target_tank2;//target list
    QGraphicsScene      *scene;     // Declaring the scene for rendering
tank* player1;
    QTimer          *timer1;
tank* player2;
    QTimer          *timer2;
skill *skill1,*skill2;
    QTimer * timer_prop;

    /* We declare a game timer, thanks to which
                                 * the position of the object on the scene will be changed
                                 * When acted on by keyboard keys
                                 * */

private slots:
    void slotShowBullet(QPointF start,int direction,tank* target);
    static void slothit(tank* target);

};

#endif // MAINSCENE_H
