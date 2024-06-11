#include "mywidget.h"
#include "ui_mywidget.h"
#include "ButtonOp.h"

#define back_img    ":/background.png"
#define img1        ":/record1.png"
#define img2        ":/record2.png"
#define img3        ":/operate1.png"
#define img4        ":/operate2.png"
#define img5        ":/instruct1.png"
#define img6        ":/instruct2.png"
#define img7        ":/start1.png"
#define img8        ":/start2.png"
#define recordPath  "record.txt"
#define back_sound  ":/theme.wav"
#define btn_sound   ":/button.wav"


MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{

    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/head.png"));
    this->setWindowTitle("火柴人酷跑");
    this->setFixedSize(1450,820);


    playMusic();

    //加载按钮
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



    operateMsg->setText("操作说明：\n1.W————上跳(最高连续两次)\n2.A————后退\n3.D————前进\n4.F————召唤怪兽保护自己8秒");
    instructMsg->setText("教程：\n1.碰撞障碍物减血减积分\n2.人物可以自动回血或拾取爱心回血\n3.拾取宝剑获得召唤次数\n4.拾取宝石、宝剑、血瓶增加积分");

    connect(recordBtn,&QPushButton::clicked,[=](){
        readRecord();
        recordMsg->setText("您的最高分数是：" + QString::number(maxScores) + "\n用时：" +
                           QString::number(maxSeconds / 60) + "分 " + QString::number(maxSeconds % 60) +
                           "秒\n");
        QSound::play(btn_sound);
        recordMsg->show();
    });
    connect(operateBtn,&QPushButton::clicked,[=](){
        QSound::play(btn_sound);
        operateMsg->show();
    });
    connect(instructBtn,&QPushButton::clicked,[=](){
        QSound::play(btn_sound);
        instructMsg->show();
    });
    connect(startBtn, &QPushButton::clicked, [=]() {
        QSound::play(btn_sound);
        mainwindow = new MainWindow();
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
    QPixmap pix(back_img);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void MyWidget::readRecord(){
    QFile file(recordPath);
    QTextStream in(&file);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Fail reading!\n";
        return;
    }
    in>>maxScores>>maxSeconds;
    qDebug()<<maxScores<<" "<<maxSeconds;
    file.close();
}
void MyWidget::playMusic() {
    if (!startsound) {
        startsound = new QSound(back_sound);
        startsound->setLoops(-1);
    }
    startsound->play();
}

void MyWidget::stopMusic() {
    if (startsound) {
        startsound->stop();
    }
}
QSound* MyWidget::startsound = nullptr;
