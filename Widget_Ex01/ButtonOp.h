#ifndef BUTTONOP_H
#define BUTTONOP_H
#include <QPushButton>
#include <QString>


class MyButton:public QPushButton{
public:
    static int count;//当前是第几个按钮
    QString img1,img2;
    MyButton(QString img1,QString img2);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // BUTTONOP_H
