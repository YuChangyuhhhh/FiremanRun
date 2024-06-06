#ifndef OBJECT_H
#define OBJECT_H
#include "mainwindow.h"
#include <cstdlib>  // For std::rand and std::srand
#include <ctime>    // For std::time
#include "role.h"

class Object{
private:
    QPixmap obPix;
    int speed;
    int posX,posY;
    int width,height;

public:
    Object();
    Object(int x,int y,int w,int h):posX(x),posY(y),width(w),height(h){}
    bool remain(MainWindow&); //判断物品位于屏幕
    void generateY();        //生成物品坐标Y
    bool touchRole(Role&); //判断人物物品接触
    int getPosX(){return posX;}
    int getPosY(){return posY;}
    int getWidth(){return width;}
    int getHeight(){return height;}

};

//障碍物类
class Barrier:public Object{
private:
    int power;
public:
    Barrier(int x,int y,int w,int h,int p):Object(x,y,w,h),power(p){}
    void dead();
    void hurt(Role& );
};

//墙体
class Wall:public Barrier{
public:
    Wall(MainWindow*);
};

class Cat:public Barrier{
public:

};

//血包
class Assitance:public Object{
private:
    int blood;
public:
    void assist(Role&);

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
