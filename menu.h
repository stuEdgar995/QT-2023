#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QPalette>
#include <QPixmap>

#include "mainscene.h"

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);

signals:
    void play();
    void settings();
    void exit();
};

#endif // MENU_H
