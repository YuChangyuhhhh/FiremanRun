#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>  // For std::rand and std::srand
#include <ctime>    // For std::time
#include <math.h>
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
    int power;
    int score;
public:
    Object();
    Object(int x,int y,int w,int h,int s,int p,int score, QPixmap pix,Role* r): posX(x), posY(y), width(w), height(h), speed(s), obPix(pix),role(r),power(p),score(score){}
    bool remain(MainWindow*); //判断物品位于屏幕
    void generateY();        //生成物品坐标Y
    bool touchRole(); //判断人物物品接触
    bool touchMonster(Monster* monster);
    void hurt();
    virtual void addScore();
    int getPower(){return power;}
    void setPosX(int x){posX = x;}
    int getPosX(){
        posX -= speed;
        return posX;
    }
    int getPosY(){return posY;}
    int getWidth(){return width;}
    int getHeight(){return height;}
    QPixmap getPix(){return obPix;}
    int getSpeed(){return speed;}
    Role* getRole(){return role;}

};


//子弹
class Bullet:public Object{
public:
    Bullet(MainWindow*,Role*);
};

//墙体
class Wall:public Object{
public:
    Wall(MainWindow*,Role*);

};

//猫
class Cat:public Object{
public:
    Cat(MainWindow*,Role*);
};

//血包
class Assistance:public Object{
public:
    Assistance(MainWindow*,Role*r);
};

//武器
class Sword:public Object{
public:
    Sword(MainWindow*,Role*);
    void addCalls();
    void addScore();
};

//宝石
class Jewel:public Object{
public:
    Jewel(MainWindow*,Role*);
};

#endif // OBJECT_H
