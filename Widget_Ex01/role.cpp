#include <QDebug>
#include "role.h"

#define run_1 ":/run_1.png"
#define run_2 ":/run_2.png"
#define run_3 ":/run_3.png"
#define run_4 ":/run_4.png"
#define run_5 ":/run_5.png"
#define jumpImg ":/jump.png"



Role::Role(){
    initialize();

    //********************************
    qDebug()<<"角色创建中.....角色创建成功\n您的初始血量为: "<<blood<<"\n";
    //********************************
}
void Role::initialize(){
    blood = 100;
    height = 80;
    width = 60;
    posX = 200;
    posY = 570;
    jumpNum = 2;
    down = false;
    speed = 25;
    figurePix[0] = QPixmap(run_1);
    figurePix[1] = QPixmap(run_2);
    figurePix[2] = QPixmap(run_3);
    figurePix[3] = QPixmap(run_4);
    figurePix[4] = QPixmap(run_5);
    figurePix[5] = QPixmap(jumpImg);
    figIndex = 0;
}
int Role::getPosY(){
    if(posY==570){
        jumpNum = 2;
        down = false;
    }
    if(isJump()&&!down&&posY>=200+jumpNum*185+speed){
        posY-=speed;
    }else{
        setDown();
        if(down&&posY<=570-speed){
            posY+=speed;
        }
    }
    return posY;
}
bool Role::isJump(){
    return posY<570;
}
void Role::setDown(){

    if(jumpNum==1&&posY<385+speed||jumpNum==0&&posY<200+speed){
        down = true;
    }

}
int Role::getFig(){
    if(isJump()){
        figIndex = 5;
    }else ++figIndex %= 5;
    return figIndex;
}

