#include "object.h"
#include "mainwindow.h"

#define wallImg1 ":/wall1.png"
#define wallImg2 ":/wall2.png"
#define bulletImg ":/bullet.png"
#define catImg ":/cat.png"
#define bloodImg ":/blood.png"


Object::Object(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

bool Object::remain(MainWindow* window){
    return ((posX<=window->getWidth())||posX+getWidth()>=0);
}

bool Object::touchRole(){
    return (posX<=role->getPosX()+role->getWidth()&&posX>=role->getPosX()-width
            &&posY<=role->getPosY()+role->getHeight()&&posY>=role->getPosY()-height);
}

void Object::generateY() {
    posY = 200 + (std::rand() % (650 - height - 200)); // 生成的 Y 坐标范围是 650+height 到 200
}

void Barrier::hurt(){
    getRole()->setBlood(getRole()->getBlood()-power);
}

int Barrier::getObPosX(){
    this->setPosX(this->getPosX()-this->getSpeed());
    return this->getPosX();
}

Wall::Wall(MainWindow* window,Role*r) : Barrier(window->getWidth(), 450, 60, 200 , 10 , 10 , QPixmap(wallImg1) , r){}
Cat::Cat(MainWindow* window, Role* r) : Barrier(window->getWidth(), 0, 200, 100, 30, 15, QPixmap(catImg), r) {
    generateY();
}
Bullet::Bullet(MainWindow* window, Role* r) : Barrier(window->getWidth(), 0, 30, 30, 40, 5, QPixmap(bulletImg), r) {
    generateY();
}
Assistance::Assistance(MainWindow* window, Role* r) : Barrier(window->getWidth(), 0, 90, 90, 20, -25, QPixmap(bloodImg), r) {
    generateY();
}


