#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVBoxLayout>

#include "options.h"
#include "game.h"
#include "menu.h"
#include "gamemenu.h"
#include "utils.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Menu* menu;
    Game* game_window;
    Options* options_window;
    Config* config;
    Main_Score main_score;

private slots:
    void Play();
    void Settings();
    void Exit();
   void slotGameOver(int ID);

    void openMenu();
    void closeMenu();
    void NewGame();
    void Back2Menu();

    void loadConfig(Config* config);
};


#endif // MAINWINDOW_H
