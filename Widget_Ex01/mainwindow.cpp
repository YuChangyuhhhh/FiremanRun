#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    srand(time(0));
    width = 1400;
    height = 800;
    role = new Role();
    keyWPressed = false;
    keyAPressed = false;
    keyDPressed = false;
    backPix = QPixmap(":/startBkg.png");
    groundPix = QPixmap(":/ground.png");
    bkgX = 0;
    groundX = 0;
    groundY = role->getPosY()+role->getHeight();

    setWindowTitle("火柴人跑酷");
    this->setWindowIcon(QIcon(":/gameIcon.png"));
    setFixedSize(width, height);

    timer1.setInterval(40);
    connect(&timer1, &QTimer::timeout, this, [=](){
        update();
    });
    connect(&timer1, &QTimer::timeout, this, &MainWindow::updateRolePosition);
    timer2.setInterval(350);
    connect(&timer2, &QTimer::timeout, [=]() {
        randGen = rand()%2;
        randType = rand()%25;
        if(randGen==0){
            if(randType>=0&&randType<15){
                barriers.append(new Bullet(this,role));
            }else if(randType>=15&&randType<20){
                barriers.append(new Wall(this,role));
            }else if(randType>=20&&randType<24){
                barriers.append(new Cat(this,role));
            }else{
                barriers.append(new Assistance(this,role));
            }
        }

    });
    timer1.start();
    timer2.start();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 在窗口关闭时删除 MainWindow 对象
    if (role) delete role;
    for (auto barrier : barriers) {
        if(barrier)
            delete barrier;
    }
    barriers.clear();
    QMainWindow::closeEvent(event);
}


MainWindow::~MainWindow()
{
    if (role) delete role;
    for (auto barrier : barriers) {
        delete barrier;
    }
    barriers.clear();
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // 更新背景
    bkgX -= 7;
    groundX -= 7;
    if (-bkgX >= backPix.width())
        bkgX = 0;
    if (-groundX >= groundPix.width())
        groundX = 0;

    // 绘制背景
    painter.drawPixmap(QRect(0, 0, width, groundY), backPix, QRect(-bkgX, 0, width, groundY));
    // 如果背景未覆盖整个窗口，绘制另一张背景
    if (-bkgX > (backPix.width() - width))
        painter.drawPixmap(QRect(backPix.width() + bkgX, 0, width + bkgX - backPix.width(), groundY),
                           backPix, QRect(0, 0, width + bkgX - backPix.width(), groundY));

    painter.drawPixmap(QRect(0, groundY, width, height - groundY), groundPix, QRect(-groundX, 0, width, height - 2 * groundY));
    if (-groundX > (groundPix.width() - width))
        painter.drawPixmap(QRect(groundPix.width() + groundX, groundY, width + groundX - groundPix.width(), height - groundY),
                           groundPix, QRect(0, 0, width + groundX - groundPix.width() , height - 2 * groundY));

    // 绘制角色
    painter.drawPixmap(QRect(role->getPosX(), role->getPosY(), role->getWidth(), role->getHeight()), role->figurePix[role->getFig()]);


    //绘制障碍物
    for(int i=0;i<barriers.size();i++){
        Barrier* barr = barriers[i];
        if(barr&&barr->remain(this)&&!barr->touchRole()){
            painter.drawPixmap(QRect(barr->getObPosX(),barr->getPosY(),barr->getWidth(),barr->getHeight()),barr->getPix());
        }else if(barr){
            barr->hurt();
            //qDebug()<<"您受到障碍物攻击，当前血量为："<<role->getBlood()<<" ";
            delete barr;
            barriers[i] = nullptr;
            barriers.erase(barriers.begin() + i);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Q) {
        keyWPressed = true;
    }
    if (event->key() == Qt::Key_A) {
        keyAPressed = true;
    }
    if (event->key() == Qt::Key_D) {
        keyDPressed = true;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Q) {
        keyWPressed = false;
    }
    if (event->key() == Qt::Key_A) {
        keyAPressed = false;
    }
    if (event->key() == Qt::Key_D) {
        keyDPressed = false;
    }
}

void MainWindow::updateRolePosition() {
    if (keyWPressed && role->getJumpNum() > 0) {
        role->subJumpNum();
        role->setPosY(role->getPosY() - role->getSpeed());

        qDebug()<<role->getJumpNum();
    }
    if (keyAPressed) {
        if (role->getPosX() >= role->getSpeed()) {
            role->setPosX(role->getPosX() - role->getSpeed());

        }
    }
    if (keyDPressed) {
        if (role->getPosX() <= width-role->getSpeed()) {
            role->setPosX(role->getPosX() + role->getSpeed());
        }
    }
    update();
}




