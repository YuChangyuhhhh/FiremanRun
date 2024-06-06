#include "object.h"

#define wallImg1 ":/wall1.png"
#define wallImg2 ":/wall2.png"
#define bulletImg ":/bullet.png"
#define catImg ":/cat.png"
#define bloodImg ":/blood.png"


Object::Object(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

bool Object::remain(MainWindow& mw){
    return ((posX<=mw.getWidth())||posX+getWidth()>=0);
}

bool Object::touchRole(Role & role){
    return ((posX<=role.getPosX()+role.getWidth()&&posX>=role.getPosX()-width)
            &&(posY<=role.getPosY()+role.getHeight()&&posY>=role.getPosY()-height));
}

void Object::generateY(){
    posY = 300 + (std::rand() % 7 * 50); //让物品坐标位于300~650之内
}


void Barrier::hurt(Role &role){
    role.setBlood(role.getBlood()-power);
}
Wall::Wall(MainWindow* mv) : Barrier(mv->getWidth(), 700, 60, 100,25){}



//void
