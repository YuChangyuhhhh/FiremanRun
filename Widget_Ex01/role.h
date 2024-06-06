#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QPixmap>

class Role:public QObject{
    Q_OBJECT
private:
    int blood;
    int posX,posY;
    int width,height;
    int speed;
    int jump;
    QTimer timer;
    int figIndex;

public:
    QPixmap figurePix[5];

    Role();
    void initialize();
    void setBlood(int blood){this->blood = blood;}
    int getBlood(){return blood;}
    int getWidth(){return width;}
    int getHeight(){return height;}
    int getPosX(){return posX;}
    int getPosY(){return posY;}
    int getFigIndex(){return figIndex;}
    //void jump();

public slots:
    void changeFig();

};

#endif // ROLE_H
