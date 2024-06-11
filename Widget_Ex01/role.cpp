#include "role.h"

#define run_1       ":/run_1.png"
#define run_2       ":/run_2.png"
#define run_3       ":/run_3.png"
#define run_4       ":/run_4.png"
#define run_5       ":/run_5.png"
#define jumpImg     ":/jump.png"
#define monImg1     ":/monster1.png"
#define monImg2     ":/monster2.png"
#define monImg3     ":/monster3.png"
#define monImg4     ":/monster4.png"


#define JumpHeight  250
#define SpeedX      20
#define SpeedY      15
#define Height      50
#define Width       40
#define PosY        600
#define Distance    100
#define MWidth      60
#define MHeight     80

Role::Role(){
    initialize();

    //********************************
    qDebug()<<"The role is generating.....success!\nYour initial blood is: "<<blood<<"\n";
    //********************************
}
void Role::initialize(){
    blood = 100;
    scores = 0;
    height = Height;
    width = Width;
    posX = 200;
    posY = PosY;
    jumpNum = 2;
    down = false;
    speedX = SpeedX;
    speedY = SpeedY;
    calls = 0;
    figurePix[0] = QPixmap(run_1);
    figurePix[1] = QPixmap(run_2);
    figurePix[2] = QPixmap(run_3);
    figurePix[3] = QPixmap(run_4);
    figurePix[4] = QPixmap(run_5);
    figurePix[5] = QPixmap(jumpImg);
    figIndex = 0;
}
int Role::getPosY(){
    if(posY==PosY){
        jumpNum = 2;
        down = false;
    }
    if(isJump()&&!down&&posY>=PosY-2*JumpHeight+jumpNum*JumpHeight+speedY){
        posY -= speedY;

    }else{
        setDown();
        if(down&&posY<=PosY-speedY){
            posY += speedY;
        }
    }

    return posY;
}
bool Role::isJump(){
    return posY<PosY;
}
void Role::setDown(){
    if((jumpNum==1&&posY<PosY-JumpHeight+speedY)||(jumpNum==0&&posY<PosY-JumpHeight*2+speedY)){
        down = true;
    }
}

void Role::updateStatus(){
    if(!isDead()&&blood<=99){
        blood += 1;
        scores += 10;
    }
}
int Role::getFigIndex(){
    if(isJump()){
        figIndex = 5;
    }else ++figIndex %= 5;
    return figIndex;
}
Monster::Monster(Role* role):Role(role->getPosX()+Distance,role->getPosY(),role->getWidth(),role->getHeight()),role(role){
    //blood = 0xffffffff;
    liveTime = 200;
    monPix[0] = QPixmap(monImg1);
    monPix[1] = QPixmap(monImg2);
    monPix[2] = QPixmap(monImg3);
    monPix[3] = QPixmap(monImg4);
    figIndex = 0;
}
void Monster::updateStatus(){
    setPosX(role->getPosX()+Distance);
    setPosY(role->getPosY());
    liveTime--;
}


