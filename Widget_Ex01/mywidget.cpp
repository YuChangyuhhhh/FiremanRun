#include "mywidget.h"
#include "ui_mywidget.h"
#include "ButtonOp.h"
#include <QPushButton>
#include <QIcon>
#include <QMessageBox>

#define img1 ":/record1.png"
#define img2 ":/record2.png"
#define img3 ":/operate1.png"
#define img4 ":/operate2.png"
#define img5 ":/instruct1.png"
#define img6 ":/instruct2.png"
#define img7 ":/start1.png"
#define img8 ":/start2.png"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{

    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/head.png"));
    this->setWindowTitle("火柴人酷跑");
    this->setFixedSize(1450,820);

    MyButton* recordBtn = new MyButton(img1,img2);
    recordBtn->setParent(this);
    MyButton* operateBtn = new MyButton(img3,img4);
    operateBtn->setParent(this);
    MyButton* instructBtn = new MyButton(img5,img6);
    instructBtn->setParent(this);
    MyButton* startBtn = new MyButton(img7,img8);
    startBtn->setParent(this);


    QMessageBox* recordMsg = new QMessageBox(this);
    QMessageBox* operateMsg = new QMessageBox(this);
    QMessageBox* instructMsg = new QMessageBox(this);

    recordMsg->setFont(QFont("STKaiti",  12));
    operateMsg->setFont(QFont("STKaiti", 12));
    instructMsg->setFont(QFont("STKaiti", 12));


    recordMsg->setText("您的最高分数是：\n用时：  秒\n");
    operateMsg->setText("操作说明：\n1.W————上跳(最高连续两次)\n2.A————后退\n3.D————前进");
    instructMsg->setText("教程：\n1.碰撞障碍物减血\n2.人物可以自动回血或拾取爱心回血\n3.拾取小锤清除障当前碍物");

    connect(recordBtn,&QPushButton::clicked,[=](){
        recordMsg->show();
    });
    connect(operateBtn,&QPushButton::clicked,[=](){
        operateMsg->show();
    });
    connect(instructBtn,&QPushButton::clicked,[=](){
        instructMsg->show();
    });
    connect(startBtn, &QPushButton::clicked, [=]() {
        mainwindow = new MainWindow;
        mainwindow->show();
        this->showMinimized();
    });

}

MyWidget::~MyWidget()
{
    delete ui;
}

//主页背景
void MyWidget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix(":/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
