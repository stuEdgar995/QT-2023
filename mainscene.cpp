#include "mainscene.h"
#include "map_creator.h"
#include "prop.h"

#include<QRandomGenerator>
#include <QApplication>
#include <QDebug>

QList<QGraphicsItem *> MainScene::target_tank1;
QList<QGraphicsItem *> MainScene::target_tank2;
MainScene::MainScene(QWidget *parent,Config* config)
    : QGraphicsView(parent) {

    //Get the size of the widget
    int w = QGuiApplication::screens().at(0)->availableGeometry().width() /2;
    int h = QGuiApplication::screens().at(0)->availableGeometry().height() /2;

    scene = new QGraphicsScene();   // Initialize the scene for rendering
    this->resize(w*2, h*2 - 75);

    //Set the scene size
    scene->setSceneRect(-w,-h+75,w*2 -2,h*2 - 75);

    this->setScene(scene);

    this->setRenderHint(QPainter::Antialiasing); //Use Antialiasing
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable the horizontal scrollbar
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Disable the vertical scrollbar
    this->setAlignment(Qt::AlignCenter);                        // Binding the content to the center
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


    QBrush back_brush(QColor(255, 243, 240)); //bricks & box
    //QBrush back_brush(QColor(224, 255, 224)); //forest

    scene->setBackgroundBrush(back_brush);

    scene->addLine(-w,-h + 75, w,-h + 75, QPen(Qt::black));//upper bound
    scene->addLine(-w,h, w,h, QPen(Qt::black));//lower bound
    scene->addLine(-w,-h + 75, -w,h, QPen(Qt::black));//left bound
    scene->addLine( w,-h + 75, w,h, QPen(Qt::black));//right bound


    MapCreator map_creator;
    map_creator.CreateMap(scene);

    //如果要写放置墙体的技能，需要在构造一个墙体后连接以下内容，如果构造的墙体无特殊行为则可以无视。
    foreach(Wall* wall,map_creator.w_list){
        connect(this,&MainScene::signal_bullet_position,wall,&Wall::slot_destoryer);
        connect(wall,&Wall::signal_back_position,this,&MainScene::slot_get_wall_position);
        // connect(this,&MainScene::signal_tank_position,wall,&Wall::slot_get_tank_position);
        connect(this,&MainScene::signal_tank_collision,wall,&Wall::slot_get_tank_collision);
    }

    tank::num_of_tanks = 0;
    player1 = new tank(nullptr,config?(config->visible) : false);
    player2 = new tank(nullptr,config?(config->visible) : false);
    player1->target=player2;
    player2->target=player1;

    scene->addItem(player1);   // Add a tank to the scene
    player1->setPos(-580,280);
    scene->addItem(player2);
    player2->setPos(570,-200);

    skill1 = new skill(nullptr);
    scene->addItem(skill1);
    skill1->setPos(-w,350);

    skill2 = new skill(nullptr);
    scene->addItem(skill2);
    skill2->setPos(700,350);

    player1->skill=skill1;
    player2->skill=skill2;

    connect(player1,&tank::signal_tank_position,this,&MainScene::slot_get_tank_position);
    connect(this,&MainScene::signal_prop_position,player1,&tank::slot_check_prop);
    connect(player2,&tank::signal_tank_position,this,&MainScene::slot_get_tank_position);
    connect(this,&MainScene::signal_prop_position,player2,&tank::slot_check_prop);

    connect(player1,&tank::signal_tank_collision,this,&MainScene::slot_get_tank_collision);
    connect(player2,&tank::signal_tank_collision,this,&MainScene::slot_get_tank_collision);
    

    timer1 = new QTimer();
    connect(timer1, &QTimer::timeout, player1, &tank::slotMove1);
    connect(timer1, &QTimer::timeout, player1, &tank::slotShoot1);
    connect(timer1, &QTimer::timeout, player1, &tank::slotSkill1);
    timer1->start(1000 / 50);

    timer2 = new QTimer();
    connect(timer2, &QTimer::timeout, player2, &tank::slotMove2);
    connect(timer2, &QTimer::timeout, player2, &tank::slotShoot2);
    connect(timer2, &QTimer::timeout, player2, &tank::slotSkill2);
    timer2->start(1000 / 50);

    this->setScene(scene);
    connect (player1,&tank::signalShootBullet,this,&MainScene::slotShowBullet);
    connect (player2,&tank::signalShootBullet,this,&MainScene::slotShowBullet);
    
    connect (player1,&tank::signalDamage,this,&MainScene::signalConnect);
    connect (player2,&tank::signalDamage,this,&MainScene::signalConnect);

    timer_prop = new QTimer();
    connect(timer_prop,&QTimer::timeout,this,&MainScene::slot_make_prop);
    timer_prop->start(1000 * config->prop_time);
}

void MainScene::slotShowBullet(QPointF start,int direction,tank* target)
{
    //Add a bullet to the scene
    Bullet *bullet=new Bullet(start,direction,target);
    scene->addItem(bullet);
    connect (bullet,&Bullet::signalhit,this,&MainScene::slothit);
    connect (bullet,&Bullet::signal_send_position,this,&MainScene::slot_get_bullet_position);
    connect (this,&MainScene::signal_wall_positon,bullet,&Bullet::slot_check_wall);
}

void MainScene::slothit(tank* target)
{
    target->hit(1);
}

void MainScene::slot_get_bullet_position(qreal px,qreal py){
    emit signal_bullet_position(px,py);
}

void MainScene::slot_get_wall_position(qreal px,qreal py){
    emit signal_wall_positon(px,py);
}

void MainScene::slot_get_tank_position(qreal px,qreal py){
    emit signal_tank_position(px,py);
}

void MainScene::slot_get_prop_posotion(qreal px,qreal py,int type){
    emit signal_prop_position(px,py,type);
}

void MainScene::slot_get_tank_collision(QGraphicsItem* pitem){
    emit signal_tank_collision(pitem);
}

void MainScene::slot_make_prop(){
    // const int maxAttempts = 10;
    const int maxAttempts = 1;
    //Get the size of the widget
    int type = QRandomGenerator::global()->bounded(4);
    Prop* prop = new Prop(nullptr,type);
    for (int i = 0; i < maxAttempts; ++i) {
        // 生成随机位置
        // qreal x = QRandomGenerator::global()->generateDouble() * w - w / 2;
        // qreal y = QRandomGenerator::global()->generateDouble() * h - h / 2;

        qreal x = -25;
        qreal y = 25;
        // 检查点周围是否存在已经构造的物体
        bool hasCollisions = false;
        prop -> setPos(x,y);
        QGraphicsScene *temp = scene;
        if(temp->collidingItems(prop).isEmpty()){
            hasCollisions = true;
        }
        if(hasCollisions){
            scene -> addItem(prop);
            connect(this,&MainScene::signal_tank_position,prop,&Prop::slot_get_tank_posotion);
            connect(prop,&Prop::signal_send_position,this,&MainScene::slot_get_prop_posotion);
            return;
        }
    }
    prop -> deleteLater();
    qDebug() << "UnLucky!";
    return;
}
