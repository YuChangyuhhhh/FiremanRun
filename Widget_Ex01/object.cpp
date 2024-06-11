#include "object.h"
#include "mainwindow.h"

#define wallImg1      ":/wall1.png"
#define wallImg2      ":/wall2.png"
#define bulletImg     ":/bullet.png"
#define catImg        ":/cat.png"
#define bloodImg      ":/blood.png"
#define swordImg      ":/sword.png"
#define jewelImg      ":/jewel.png"
#define wallSpeed     10
#define bulletSpeed   13
#define catSpeed      12
#define assistSpeed   8
#define swordSpeed    6
#define jewelSpeed    9




Object::Object(){
    srand(time(0));
}

bool Object::remain(MainWindow* window){
    return ((posX<=window->getWidth())||posX+getWidth()>=0);
}

bool Object::touchRole(){
    return (posX<=role->getPosX()+role->getWidth()&&posX>=role->getPosX()-width
            &&posY<=role->getPosY()+role->getHeight()&&posY>=role->getPosY()-height);
}

bool Object::touchMonster(Monster* monster){
    return (posX<=monster->getPosX()+monster->getWidth()&&posX>=monster->getPosX()-width
            &&posY<=monster->getPosY()+monster->getHeight()&&posY>=monster->getPosY()-height);
}

void Object::generateY() {
    posY = 200 + (rand() % (650 - height - 200)); // 生成的 物体 是 650+height 到 200
}

void Object::hurt(){
    if(power>0&&role->getBlood()>=power||power<0&&role->getBlood()<=100+power)
        role->setBlood(role->getBlood()-power);
    else if(role->getBlood()>0&&power>0){
        role->setBlood(0);
    }
}


void Object::addScore(){
    if(touchRole())
        role->setScores(role->getScores()+score);
}

void Sword::addScore(){
    Object::addScore();
    addCalls();
}
void Sword::addCalls(){
    getRole()->setCalls(getRole()->getCalls()+1);
}

Wall::Wall(MainWindow* window,Role*r) : Object(window->getWidth(), 550, 30, 100 , wallSpeed , 10 , -50 , QPixmap(wallImg1) , r){}
Cat::Cat(MainWindow* window, Role* r) : Object(window->getWidth(), 0, 150, 75, catSpeed, 15, -100 , QPixmap(catImg), r) {
    generateY();
}
Bullet::Bullet(MainWindow* window, Role* r) : Object(window->getWidth(), 0, 30, 30, bulletSpeed, 5, -20 ,QPixmap(bulletImg), r) {
    generateY();
}
Assistance::Assistance(MainWindow* window, Role* r) : Object(window->getWidth(), 0, 90, 90, assistSpeed, -25, 50 , QPixmap(bloodImg), r) {
    generateY();
}
Sword::Sword(MainWindow* window, Role* r) : Object(window->getWidth(), 0, 75, 75, swordSpeed, 0, 100 , QPixmap(swordImg), r) {
    generateY();
}
Jewel::Jewel(MainWindow* window, Role* r) : Object(window->getWidth(), 500, 90, 90, jewelSpeed, 0, 200 , QPixmap(jewelImg), r) {}





