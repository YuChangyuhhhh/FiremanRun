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
    QTimer timer;
    int figIndex;
    int jumpNum = 2;
    bool down;
public:
    QPixmap figurePix[6];

    Role();
    void initialize();
    bool isJump();
    void subJumpNum(){jumpNum--;}
    int getJumpNum(){return jumpNum;}
    void setDown();
    void setBlood(int blood){this->blood = blood;}
    void setPosX(int x){posX = x;}
    void setPosY(int y){posY = y;}
    int getBlood(){return blood;}
    int getWidth(){return width;}
    int getHeight(){return height;}
    int getPosX(){return posX;}
    int getPosY();
    int getSpeed(){return speed;}
    int getFigIndex(){return figIndex;}
    //void jump();

public slots:
    int getFig();

};

#endif // ROLE_H
