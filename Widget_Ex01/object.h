#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>  // For std::rand and std::srand
#include <ctime>    // For std::time
#include "role.h"
//#include "mainwindow.h"

class MainWindow;
class Object{
private:
    QPixmap obPix;
    int speed;
    int posX,posY;
    int width,height;
    Role* role;
public:
    Object();
    Object(int x,int y,int w,int h, int s,QPixmap pix,Role* r): posX(x), posY(y), width(w), height(h), speed(s), obPix(pix),role(r){}
    bool remain(MainWindow*); //判断物品位于屏幕
    void generateY();        //生成物品坐标Y
    bool touchRole(); //判断人物物品接触

    void setPosX(int x){posX = x;}
    virtual int getPosX(){return posX;}
    int getPosY(){return posY;}
    int getWidth(){return width;}
    int getHeight(){return height;}
    QPixmap getPix(){return obPix;}
    int getSpeed(){return speed;}
    Role* getRole(){return role;}

};

//障碍物类
class Barrier:public Object{
private:
    int power;
public:
    Barrier(int x,int y,int w,int h,int s,int p,QPixmap pix,Role* r):Object(x,y,w,h,s,pix,r),power(p){}
    void hurt();
    int getObPosX();

};

//子弹
class Bullet:public Barrier{
public:
    Bullet(MainWindow*,Role*r);
};

//墙体
class Wall:public Barrier{
public:
    Wall(MainWindow*,Role*r);

};

//猫
class Cat:public Barrier{
public:
    Cat(MainWindow*,Role*r);
};

//血包
class Assistance:public Barrier{
public:
    Assistance(MainWindow*,Role*r);
};

//武器
class Weapon:public Object{
public:
    void clean();
};

class Coin:public Object{
private:

    int pixIndex;
    int score;
public:
    void addScore(Role&);
};

//宝石
class Jewel:public Object{
private:
    int score;
public:
    void addScore(Role&);
};

#endif // OBJECT_H
