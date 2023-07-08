#include <tank.h>

int tank::num_of_tanks=0;
tank::tank(QObject *parent,bool visible) :
    QObject(parent), QGraphicsItem()
{
    health=1;
    id=++num_of_tanks;
    direction=0;
    setRotation(0);
    movingSpeed=3;

    this->config_visible=visible;
    visibleTime=3;
    coolDownTime=20;

    leftTime=0;
    skillAvaliable=true;
    protectTime=0;
}

tank::~tank()
{

}


void tank::slotMove1()
{
    emit signal_tank_position(this->x(),this->y());
    if(GetAsyncKeyState(VK_LEFT)){
        //if(!visible && !force_vitualable) setVisible(false);
        direction = 1;
        setRotation(90*1);  // Rotating the object
        setPos(mapToParent(0, movingSpeed));
        if(!scene()->collidingItems(this).isEmpty() && !through_wall){
            for(auto pitem:scene()->collidingItems(this)) {
                emit(signal_tank_collision(pitem));
            }
            setPos(mapToParent(0, -movingSpeed));
        }
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        //if(!visible && !force_vitualable) setVisible(false);
        direction = 3;
        setRotation(90*3); // Rotating the object
        setPos(mapToParent(0,movingSpeed));
        if(!scene()->collidingItems(this).isEmpty() && !through_wall){
            for(auto pitem:scene()->collidingItems(this)) {
                emit(signal_tank_collision(pitem));
            }
            setPos(mapToParent(0, -movingSpeed));
        }
    }
    if(GetAsyncKeyState(VK_UP)){
        //if(!visible && !force_vitualable) setVisible(false);
        direction = 2;
        setRotation(90*2); // Rotating the object
        setPos(mapToParent(0,movingSpeed));
        if(!scene()->collidingItems(this).isEmpty() && !through_wall){
            for(auto pitem:scene()->collidingItems(this)) {
                emit(signal_tank_collision(pitem));
            }
            setPos(mapToParent(0, -movingSpeed));
        }
    }
    if(GetAsyncKeyState(VK_DOWN)){
        //if(!visible && !force_vitualable) setVisible(false);
        direction = 0;
        setRotation(90*0); // Rotating the object
        setPos(mapToParent(0,movingSpeed));
        if(!scene()->collidingItems(this).isEmpty() && !through_wall){
            for(auto pitem:scene()->collidingItems(this)) {
                emit(signal_tank_collision(pitem));
            }
            setPos(mapToParent(0, -movingSpeed));
        }
    }

    // borders check，但width和height还不对，暂时没搞清楚怎么设置
    if(this->x() < -(width / 2)){
        this->setX(-(width / 2) + 1);       //left
    }
    if(this->x() > (width / 2)){
        this->setX((width/2) - 1);        //right
    }

    if(this->y()< -(height / 2)){
        this->setY(-(height / 2) + 1);       //up
    }
    if(this->y()> (height / 2)){
        this->setY((height / 2) - 1);        //down
    }

    //碰到道具，触发signalUseTool

}

void tank::slotMove2(){
    emit signal_tank_position(this->x(),this->y());
    if(GetAsyncKeyState('A')){
        //if(!visible && !force_vitualable) setVisible(false);
        direction = 1;
        setRotation(90*1);  // Rotating the object
        setPos(mapToParent(0, movingSpeed));
        //遇到障碍物，不动
        if(!scene()->collidingItems(this).isEmpty() && !through_wall){
            for(auto pitem:scene()->collidingItems(this)) {
                emit(signal_tank_collision(pitem));
            }
            setPos(mapToParent(0, -movingSpeed));
        }
    }
    if(GetAsyncKeyState('D')){
        //if(!visible && !force_vitualable) setVisible(false);
        direction = 3;
        setRotation(90*3); // Rotating the object
        setPos(mapToParent(0,movingSpeed));
        if(!scene()->collidingItems(this).isEmpty() && !through_wall){
            for(auto pitem:scene()->collidingItems(this)) {
                emit(signal_tank_collision(pitem));
            }
            setPos(mapToParent(0, -movingSpeed));
        }
    }
    if(GetAsyncKeyState('W')){
        //if(!visible && !force_vitualable) setVisible(false);
        direction = 2;
        setRotation(90*2); // Rotating the object
        setPos(mapToParent(0,movingSpeed));
        if(!scene()->collidingItems(this).isEmpty() && !through_wall){
            for(auto pitem:scene()->collidingItems(this)) {
                emit(signal_tank_collision(pitem));
            }
            setPos(mapToParent(0, -movingSpeed));
        }
    }
    if(GetAsyncKeyState('S')){
        //if(!visible && !force_vitualable) setVisible(false);
        direction = 0;
        setRotation(90*0); // Rotating the object
        setPos(mapToParent(0,movingSpeed));
        if(!scene()->collidingItems(this).isEmpty() && !through_wall){
            for(auto pitem:scene()->collidingItems(this)) {
                emit(signal_tank_collision(pitem));
            }
            setPos(mapToParent(0, -movingSpeed));
        }
    }

    // borders check，但width和height还不对，暂时没搞清楚怎么设置
    if(this->x() < -(width / 2)){
        this->setX(-(width / 2) + 1);       //left
    }
    if(this->x() > (width / 2)){
        this->setX((width/2) - 1);        //right
    }

    if(this->y()< -(height / 2)){
        this->setY(-(height / 2) + 1);       //up
    }
    if(this->y()> (height / 2)){
        this->setY((height / 2) - 1);        //down
    }

}

void tank::slotShoot1(){
    visibleTime -= 0.02;
    if(visibleTime<=0 && !force_vitualable && !config_visible) setVisible(false);
    if(GetAsyncKeyState('K')){
        setVisible(true);
        visibleTime = 1;
        emit signalShootBullet(QPointF(this->x(),this->y()),direction,target);
    }
}

void tank::slotShoot2(){
    visibleTime -= 0.02;
    if(visibleTime<=0 && !force_vitualable && !config_visible) setVisible(false);
    if(GetAsyncKeyState('C')){
        setVisible(true);
        visibleTime = 1;
        emit signalShootBullet(QPointF(this->x(),this->y()),direction,target);
    }
}

void tank::slotSkill1(){
    leftTime-= 0.02;
    protectTime -= 0.02;
    if(leftTime<=0){
        skillAvaliable=true;
        skill->update(true);
    }
    if(GetAsyncKeyState('L') && skillAvaliable){
        leftTime=coolDownTime;
        skillAvaliable=false;
        skill->update(false);
        protectTime=3;
        qDebug()<<"player1 uses his skill";
    }
}

void tank::slotSkill2(){
    leftTime-= 0.02;
    if(leftTime<=0){
        skillAvaliable=true;
        skill->update(true);
    }
    if(GetAsyncKeyState('F') && skillAvaliable){
        leftTime=coolDownTime;
        skillAvaliable=false;
        skill->update(false);
        protectTime=3;
        qDebug()<<"player2 uses his skill";
    }
}

void tank::hit(int damage)
{
    if(protectTime>0){
        qDebug()<<"protected";
        return;
    }
    health -= damage;   // Reduce Target Health
    qDebug() << "hitted, health = " << health;
    if (health == 0){
        emit signalDamage(health,id);}
    //if(health <= 0) this->deleteLater();
}

//绘制人物，这里先直接把坦克拿来用了
QRectF tank::boundingRect() const
{
    qreal scale_factor = 0.8;
    return QRectF(-20*scale_factor, -25*scale_factor, 40*scale_factor, 50*scale_factor);   // Limiting the area in which the tank lies
}

QPainterPath tank::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (id == 1) {
        painter->setBrush(Qt::blue);
    } else if (id == 2) {
        painter->setBrush(Qt::green);
    }

    qreal scale_factor = 0.8;
    painter->drawRect(-15*scale_factor,-25*scale_factor,30*scale_factor,40*scale_factor);//body
    painter->setBrush(Qt::black);
    painter->drawRect(-20*scale_factor,-20*scale_factor,5*scale_factor,30*scale_factor);//left wheel
    painter->drawRect(15*scale_factor,-20*scale_factor,5*scale_factor,30*scale_factor);//right wheel
    painter->drawRect(-5*scale_factor,-5*scale_factor,10*scale_factor,30*scale_factor);//gun


    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void tank::slot_change_through_wall(){
    through_wall = true;
}

void tank::slot_change_visiable(){
    force_vitualable = !force_vitualable;
}

void tank::slot_change_speed(){
    movingSpeed = 5;
}
void tank::slot_speed_back(){
    // movingSpeed = 5.0;
}

void tank::slot_check_prop(qreal px,qreal py,int type){
    if(abs(this->x() - px)+abs(this->y() - py) < 80){
        slot_get_prop(type);
    }
}

void tank::slot_get_prop(int type){
    /*
     type:
            0. speed
            1. healing
            2. virtualable
            3. breakwall
    */
    if (type == 1){
        health += 1;
        qDebug() << "health: " << health;
        return;}
    QTimer* timer = new QTimer(this);
    timer -> setSingleShot(true);
    timer -> setInterval(5000);
    if (type == 0){
        this -> slot_change_speed();
        qDebug() << "Speed++";
        connect(timer,&QTimer::timeout,this,&tank::slot_speed_back);
    }else if(type == 2){
        target -> setVisible(true);
        target -> slot_change_visiable();
        qDebug() << "force visiable";
        connect(timer,&QTimer::timeout,this,&tank::slot_change_visiable);
    }else if(type == 3){
        this -> slot_change_through_wall();
        connect(timer,&QTimer::timeout,target,&tank::slot_change_through_wall);
    }
    timer -> start();

}

void tank::send_position_byhand(){
    emit signal_tank_position(this->x(),this->y());
}
