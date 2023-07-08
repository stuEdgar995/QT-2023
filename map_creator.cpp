#include "map_creator.h"
#include <QScreen>
#include <QApplication>
#include <QDebug>
#include <QChar>
MapCreator::MapCreator(const std::string& name_of_file) : file_name(name_of_file) {}

void MapCreator::CreateMap(QGraphicsScene *scene){
    QFile file(":/bg/maps/map_4.txt");

    int w = QGuiApplication::screens().at(0)->availableGeometry().width() / 2;
    int h = QGuiApplication::screens().at(0)->availableGeometry().height() / 2;

    qreal wall_size = 41;

    if (file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        int row = 0; // rows
        int col = 0; //columns

        int num = 1;
        char * buffer=new char[num];
        int length = 0;
        while((length=file.read(buffer,1))!=0) //while file isn't ended
        {

            if (buffer[0] == '\n') {
                ++row;
                col = 0;
            } else if (buffer[0] != ' ') {
                ++col;
            }

            if (buffer[0] == '1') {

                Wall* wall = new Wall(scene);
                scene->addItem(wall);
                wall->setPos((col - 1) * wall_size -w, row * wall_size-h + 75 + 1);

            }

            else if (buffer[0] == '2') {

                Wall* wall = new Wall(scene,0,true);
                scene->addItem(wall);
                wall->setPos((col - 1) * wall_size -w, row * wall_size-h + 75 + 1);
                w_list.insert(wall);
            }

            else if(buffer[0] == '3') {
                Wall* wall = new Wall(scene,true);
                scene->addItem(wall);
                wall->setPos((col - 1) * wall_size -w, row * wall_size-h + 75 + 1);
                w_list.insert(wall);
            }

        }

        file.close();
    }
}
