#ifndef TANK_H
#define TANK_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>
#include <QPainterPath>
#include <QGraphicsScene>

#include "windows.h"
#include <QScreen>
#include <QGuiApplication>
#include <QKeyEvent>
#include <skill.h>

class tank : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit tank(QObject *parent = 0,bool visible=false);
    ~tank();
    tank* target; //对手，用于传给子弹判定有无打中
    skill* skill;
    void hit(int damage);
    QPointF toolPosition;
    static int num_of_tanks;
    void send_position_byhand();

signals:
    void signalShootBullet(QPointF start,int direction,tank* target);
    void signalSkillTiming(int leftTime);
    void signalUseTool(tank* user);   //不太确定道具生效的判定应该放在道具里or玩家里实现
    void signalDamage(int health,int id);
    void signal_tank_position(qreal px,qreal py);
    void signal_tank_collision(QGraphicsItem* pitem);
    //坦克在移动的时候发送位置给mainscene，mainscene分发给墙体和道具，随后道具回传位置信息给坦克，用来检测是否生效。

public slots:
    void slotMove1();
    void slotMove2();

    void slotShoot1();
    void slotShoot2();

    void slotSkill1();
    void slotSkill2();

    //得到道具的类型
    void slot_check_prop(qreal px,qreal py,int type);
    void slot_get_prop(int type);
    //用于处理延时道具的槽
    void slot_change_through_wall();
    void slot_change_visiable();
    void slot_change_speed();
    void slot_speed_back();

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int width = QGuiApplication::screens().at(0)->availableGeometry().width();
    int height = QGuiApplication::screens().at(0)->availableGeometry().height();

    int health;
    int id;
    double coolDownTime;
    double leftTime;
    bool skillAvaliable;
    double protectTime;

    int direction;
    bool visible;
    double visibleTime;
    bool crossWall;
    double movingSpeed;
    double updateTime;

    bool through_wall = false;
    bool force_vitualable = false;
    bool config_visible = false;

};

#endif // TANK_H
