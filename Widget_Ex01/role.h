#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QDebug>

class Role:public QObject{
    Q_OBJECT
private:
    int blood;
    int scores;
    int posX,posY;
    int width,height;
    int speedX;
    int speedY;
    int figIndex;
    int jumpNum = 2;
    bool down;
    int calls;
public:
    QPixmap figurePix[6];

    Role();
    Role(int x,int y,int w,int h):posX(x),posY(y),width(w),height(h){}
    void initialize();
    bool isJump();
    int getJumpNum(){return jumpNum;}
    void setJumpNum(int num){
        jumpNum = num;
    }
    void setDown();
    bool isDead(){return blood<=0;}
    virtual void updateStatus();
    void setBlood(int blood){this->blood = blood;}
    void setScores(int scores){this->scores = scores;}
    void setPosX(int x){posX = x;}
    void setPosY(int y){
        posY = y;
        jumpNum--;
    }
    void setCalls(int calls){this->calls = calls;}
    int getBlood(){return blood;}
    int getScores(){return scores;}
    int getWidth(){return width;}
    int getHeight(){return height;}
    int getPosX(){return posX;}
    int getPosY();
    int getSpeedX(){return speedX;}
    int getSpeedY(){return speedY;}
    int getCalls(){return calls;}
    virtual int getFigIndex();
};

class Monster:public Role{
private:
    Role* role;
    int liveTime;
    int figIndex;
public:
    QPixmap monPix[4];
    Monster(Role*);
    int getFigIndex(){return ++figIndex%4;}
    void updateStatus();
    int getLiveTime(){return liveTime;}
    int getPosY(){return role->getPosY();}
};


#endif // ROLE_H
