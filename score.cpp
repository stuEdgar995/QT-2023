#include "score.h"
#include <string>
Score::Score(Main_Score main_score){

health=30;
maxHealth=health;

    QLabel *labelscore1 = new QLabel(this);
    labelscore1->setFrameStyle(QFrame::Plain | QFrame::Box);
    labelscore1->setStyleSheet("background-color:red;");
    labelscore1->setText(std::to_string(main_score.player_1_score).c_str());

    QFont font1= labelscore1->font();
    font1.setPixelSize(20);
    labelscore1->setFont(font1);

    labelscore1->setGeometry(0,0,50,50 );
    labelscore1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    QLabel *labelscore2 = new QLabel(this);
    labelscore2->setFrameStyle(QFrame::Plain | QFrame::Box);
    labelscore2->setStyleSheet("background-color:red;");
    labelscore2->setText(std::to_string(main_score.player_2_score).c_str());


    QFont font2= labelscore2->font();
    font2.setPixelSize(20);
    labelscore2->setFont(font2);

    labelscore2->setGeometry(SCORE_WIDTH - 50,0,50,50 );
    labelscore2->setAlignment(Qt::AlignRight | Qt::AlignVCenter);


    QPalette p(palette());
    p.setColor(QPalette::Window, QColor(255, 243, 240)); //bricks & box
    //p.setColor(QPalette::Window, QColor(224, 255, 224)); //forest

    this->setAutoFillBackground(true);
    this->setPalette(p);

    this->setFixedHeight(50);
}


void Score::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter1(this);
    QPainter painter2(this);

        painter1.save();
        painter1.setBrush(Qt::blue);
        if(!hp1.isNull())
            painter1.drawRect(hp1);
        painter1.restore();

        painter2.save();
        painter2.setBrush(Qt::green);
        if(!hp2.isNull())
            painter2.drawRect(hp2);
        painter2.restore();
}

void Score::slotDamage(int health,int ID){
   std::ofstream fout;
   if(ID==1){
        if(health<=0){
              std::ofstream fout;
                fout.open("Results.txt");
                fout << "Player2 WON!!!!";
                emit signalEndOfTheGame(2);
           }
   }
   else if(ID==2){
        if(health<=0){
                fout.open("Results.txt");
                fout << "Player1 WON!!!!";
                emit signalEndOfTheGame(1);
           }
   }
   fout.close();
}
