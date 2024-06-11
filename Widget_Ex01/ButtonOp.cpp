#include "ButtonOp.h"
#include <QPixmap>
#include <QPainter>
int MyButton::count = -1;

MyButton::MyButton(QString img1,QString img2):img1(img1),img2(img2){
    count++;
    this->setStyleSheet("border-image:url("+img1+");");
    this->resize(150,150);
    this->move(200+300*count,500);
}

void MyButton::enterEvent(QEvent *event){
    this->setStyleSheet("border-image:url("+img2+");");
    this->resize(225,225);
}

void MyButton::leaveEvent(QEvent *event){
    this->setStyleSheet("border-image:url("+img1+");");
    this->resize(150,150);
}
