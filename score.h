#ifndef SCORE_H
#define SCORE_H


#include <QScreen>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QLabel>
#include <QStyleOptionGraphicsItem>
#include <fstream>
#include "utils.h"
class Score : public QWidget
{
    Q_OBJECT
public:
    explicit Score(Main_Score main_score);

protected:
    void paintEvent(QPaintEvent *event);

signals:
void signalEndOfTheGame(int ID);
public slots:
void slotDamage(int health,int ID);
protected:
private:

    int SCORE_WIDTH = QGuiApplication::screens().at(0)->availableGeometry().width();
    const int length = SCORE_WIDTH / 4;

    int health;
    int maxHealth;

    QRectF hp1;
    QRectF hp2;

};


#endif // SCORE_H
