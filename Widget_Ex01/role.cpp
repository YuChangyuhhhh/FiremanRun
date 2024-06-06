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
    timer.setInterval(50);
    connect(&timer, &QTimer::timeout, this, &Role::changeFig);
    timer.start();
}
void Role::initialize(){
    blood = 100;
    height = 50;
    width = 45;
    posX = 200;
    posY = 600;
    jump = 0;
    speed = 0;
    figurePix[0] = QPixmap(run_1);
    figurePix[1] = QPixmap(run_2);
    figurePix[2] = QPixmap(run_3);
    figurePix[3] = QPixmap(run_4);
    figurePix[4] = QPixmap(run_5);

    figIndex = 0;
}

void Role::changeFig(){
    ++figIndex %= 5;
}

