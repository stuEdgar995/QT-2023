#include "mainwindow.h"
#include <QPalette>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), menu(nullptr) ,game_window(nullptr), options_window(nullptr), config(nullptr)
{
    this->setWindowIcon(QIcon(":/icons/images/icon.png"));

    QFile styleF;

    styleF.setFileName(":/styles/styles.css");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();

    this->setStyleSheet(qssStr);
    Menu* menu = new Menu(this);
    this->setCentralWidget(menu);

    this->config = new Config;

    connect(menu, &Menu::play, this, &MainWindow::Play);
    connect(menu, &Menu::settings, this, &MainWindow::Settings);
    connect(menu, &Menu::exit, this, &MainWindow::Exit);
    this->showMaximized();
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::loadConfig(Config* config) {
    this->config = config;
    main_score.reset(config->end_score);
    game_window = new Game(nullptr,config,main_score);
}

void MainWindow::Play() {
    main_score.reset();
    game_window = new Game(nullptr,this->config,main_score);
    connect(game_window, &Game::openmenu, this, &MainWindow::openMenu);
    connect(game_window,&Game::GameOver,this,&MainWindow::slotGameOver);
   this->setCentralWidget(game_window);
   this->setFocusPolicy(Qt::StrongFocus);
    game_window->show();
    game_window->setFocus();
}

void MainWindow::Settings() {
    options_window = new Options(this);
    connect(options_window,&Options::signalConfig,this,&MainWindow::loadConfig);

    options_window->exec();
}

void MainWindow::Exit() {
    QCoreApplication::quit();
}

void MainWindow::openMenu() {
    GameMenu* gamemenu = new GameMenu();
    this->setCentralWidget(gamemenu);

    //connect(gamemenu, &GameMenu::play, this, &MainWindow::Play);
    connect(gamemenu, &GameMenu::newgame, this, &MainWindow::NewGame);
    connect(gamemenu, &GameMenu::settings, this, &MainWindow::Settings);
    connect(gamemenu, &GameMenu::exit, this, &MainWindow::Exit);
}

void MainWindow::closeMenu() {
    this->setCentralWidget(game_window);
}

void MainWindow::NewGame() {
    main_score.reset();
    game_window = new Game(nullptr,this->config,main_score);
    this->setCentralWidget(game_window);
    game_window->show();
    game_window->setFocus();
    connect(game_window, &Game::openmenu, this, &MainWindow::openMenu);
     connect(game_window,&Game::GameOver,this,&MainWindow::slotGameOver);
}

void MainWindow::Back2Menu() {
    menu = new Menu(this);
    this->setCentralWidget(menu);
    connect(menu, &Menu::play, this, &MainWindow::Play);
    connect(menu, &Menu::settings, this, &MainWindow::Settings);
    connect(menu, &Menu::exit, this, &MainWindow::Exit);
}

void MainWindow::slotGameOver(int ID){

    main_score.add_score(ID);
    if(!main_score.end()) {
        game_window = new Game(nullptr,this->config,main_score);
        this->setCentralWidget(game_window);
        game_window->show();
        game_window->setFocus();
        connect(game_window, &Game::openmenu, this, &MainWindow::openMenu);
        connect(game_window,&Game::GameOver,this,&MainWindow::slotGameOver);
    }
    else {

        QWidget *game_over=new QWidget();
        this->setCentralWidget(game_over);

        QVBoxLayout* vlayout = new QVBoxLayout();
        QHBoxLayout* hlayout = new QHBoxLayout();
        QPushButton* newgame = new QPushButton("New Game");
        QPushButton* back2menu = new QPushButton("Back to Menu");
        QPushButton* exit = new QPushButton("Exit");

        game_over->setLayout(vlayout);
        hlayout->addWidget(newgame);
        hlayout->addWidget(back2menu);
        hlayout->addWidget(exit);
        hlayout->setContentsMargins(100, 100, 0, 10);



        if(ID==1){

            QLabel *label1 = new QLabel();
            label1->setFrameStyle(QFrame::Plain | QFrame::Box);
            label1->setStyleSheet("background-color:rgb(68, 70, 171);");
            label1->setText("Player1 Won!!!! Congratulations!!!");
            label1->setAlignment(Qt::AlignTop | Qt::AlignCenter);

            QFont font1= label1->font();
            font1.setPixelSize(75);
            label1->setFont(font1);

            label1->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            vlayout->addWidget(label1);

        }else if(ID==2){

            QLabel *label2 = new QLabel();
            label2->setFrameStyle(QFrame::Plain | QFrame::Box);
            label2->setStyleSheet("background-color:rgb(68, 70, 171);");
            label2->setText("Player2 Won!!!! Congratulations!!!");
            label2->setAlignment(Qt::AlignTop | Qt::AlignCenter);

            QFont font2= label2->font();
            font2.setPixelSize(75);
            label2->setFont(font2);

            label2->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            vlayout->addWidget(label2);

        }
        vlayout->addLayout(hlayout);

        connect(newgame, &QPushButton::clicked, this, &MainWindow::NewGame);
        connect(back2menu, &QPushButton::clicked, this, &MainWindow::Back2Menu);
        connect(exit, &QPushButton::clicked, this, &MainWindow::Exit);
    }

}
