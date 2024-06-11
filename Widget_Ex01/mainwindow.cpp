#include "mainwindow.h"
#include "MyWidget.h"
#include "ui_mainwindow.h"
#include <QDebug>

#define BulletFrequency    20
#define WallFrequency      28
#define CatFrequency       34
#define AssistFrequency    35
#define SwordFrequency     36
#define JewelFrequency     40
#define TimeIntervel1      50
#define TimeIntervel2      350
#define TimeInterval       1000
#define Genprob            2
#define TypeProb           40
#define backSpeed          7
#define backImg       ":/startBkg.png"
#define groundImg     ":/ground.png"
#define hurtImg       ":/hurt.png"
#define gameIconImg   ":/gameIcon.png"
#define gameoverImg   ":/gameover.jpg"
#define swordImg      ":/sword.png"
#define heartImg      ":/heart.png"
#define recordPath    "record.txt"
#define jump_sound    ":/jump.wav"
#define buff_sound    ":/buff.wav"
#define touch_sound   ":/touch.wav"
#define over_sound    ":/kunkun.wav"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initialize();
    connect(&timer1, &QTimer::timeout, this, [=](){
        update();
        if(role->isDead()){
            MyWidget::stopMusic();
            QSound::play(over_sound);
            if(QMessageBox::information(this, "Gameover", "游戏结束！") == QMessageBox::Ok){
                 gameover = true;
            }
            timer1.stop();
            timer2.stop();
            timer.stop();
        }
    });
    connect(&timer1, &QTimer::timeout, this, &MainWindow::keyProcess);
    connect(&timer2, &QTimer::timeout, [=]() {
        role->updateStatus();
        randGen = rand()%Genprob;
        randType = rand()%TypeProb;
        if(randGen==0){
            if(randType>=0&&randType<BulletFrequency){
                barriers.append(new Bullet(this,role));
            }else if(randType>=BulletFrequency&&randType<WallFrequency){
                barriers.append(new Wall(this,role));
            }else if(randType>=WallFrequency&&randType<CatFrequency){
                barriers.append(new Cat(this,role));
            }else if(randType>=CatFrequency&&randType<AssistFrequency){
                barriers.append(new Assistance(this,role));
            }else if(randType>=AssistFrequency&&randType<SwordFrequency){
                barriers.append(new Sword(this,role));
            }else{
                barriers.append(new Jewel(this,role));
            }
        }
    });
    connect(&timer,&QTimer::timeout,[=](){
        seconds++;
    });
    timer1.start();
    timer2.start();
    timer.start();
}

void MainWindow::initialize(){
    srand(time(0));
    width = 1400;
    height = 800;

    role = new Role();
    monster = nullptr;

    keyWPressed = false;
    keyAPressed = false;
    keyDPressed = false;
    keyFPressed = false;

    backPix = QPixmap(backImg);
    groundPix = QPixmap(groundImg);
    bkgX = 0;
    groundX = 0;
    groundY = role->getPosY()+role->getHeight();
    gameover = false;
    seconds = 0;

    setWindowTitle("火柴人跑酷");
    this->setWindowIcon(QIcon(gameIconImg));
    setFixedSize(width, height);

    timer1.setInterval(TimeIntervel1);
    timer2.setInterval(TimeIntervel2);
    timer.setInterval(TimeInterval);
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
    timer1.stop();
    timer2.stop();
    timer.stop();
    QMainWindow::closeEvent(event);
}


MainWindow::~MainWindow()
{
    if (role) delete role;
    for (auto barrier : barriers) {
        if(barrier)
            delete barrier;
    }
    barriers.clear();
    timer1.stop();
    timer2.stop();
    timer.stop();
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    // 更新背景
    bkgX -= backSpeed;
    groundX -= backSpeed;
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
    painter.drawPixmap(QRect(role->getPosX(), role->getPosY(), role->getWidth(), role->getHeight()), role->figurePix[role->getFigIndex()]);
    //绘制召唤怪物
    if(monster&&monster->getLiveTime()>0){
        monster->updateStatus();
        painter.drawPixmap(QRect(monster->getPosX(), monster->getPosY(), monster->getWidth(),monster->getHeight()),monster->monPix[monster->getFigIndex()]);
    }else if(monster&&monster->getLiveTime()<=0){
        delete monster;
        monster = nullptr;
    }


    //绘制障碍物
    for(int i=0;i<barriers.size();i++){
        Object* barr = barriers[i];
        if(barr&&barr->remain(this)&&!barr->touchRole()){
            painter.drawPixmap(QRect(barr->getPosX(),barr->getPosY(),barr->getWidth(),barr->getHeight()),barr->getPix());
        }else if(barr){
            barr->hurt();
            barr->addScore();
            if(barr->getPower()>0){
                QSound::play(touch_sound);
                painter.drawPixmap(QRect(0,0,width,height),QPixmap(hurtImg));
            }else{
                QSound::play(buff_sound);
            }

//            qDebug()<<"Your blood:"<<role->getBlood()
//                     <<" "<<"Your scores:"<<role->getScores()
//                     <<"  Call monster's num is:"<<role->getCalls();
            delete barr;
            barriers[i] = nullptr;
            barriers.erase(barriers.begin() + i);
        }
    }

    if (monster) {
        for (int i = 0; i < barriers.size(); i++) {
            Object* barr = barriers[i];
            if (barr && barr->touchMonster(monster) && barr->getPower()>0) {
                delete barr;
                barriers[i] = nullptr;
                barriers.erase(barriers.begin() + i);
            }
        }
    }

    //绘制时间、分数、大招次数和血量
    painter.setPen(Qt::black);
    painter.setFont(QFont("STKaiti", 20));
    painter.drawText(QRect(10, 10, 300, 30),
                     Qt::AlignLeft | Qt::AlignTop,
                     QString("Time: %1:%2").arg(seconds / 60, 2, 10, QLatin1Char('0')).arg(seconds % 60, 2, 10, QLatin1Char('0')));
    painter.drawText(QRect(400, 10, 300, 30), Qt::AlignLeft | Qt::AlignTop, QString("Score: %1").arg(role->getScores()));

    painter.drawPixmap(QRect(800, 10, 50, 50), QPixmap(swordImg));
    painter.drawText(QRect(830, 10, 250, 30), Qt::AlignLeft | Qt::AlignTop, QString("  : %1").arg(role->getCalls()));

    painter.drawPixmap(QRect(1200, 10, 50, 50), QPixmap(heartImg));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(1260, 20, 100, 30);  // 绘制血条背景
    painter.setBrush(Qt::green);
    painter.drawRect(1260, 20, 100 * role->getBlood() / 100, 30);  // 绘制当前血量


    //结束
    if (role->isDead()&&gameover) {
        gameover = false;
        writeToRecord();
        painter.drawPixmap(QRect(0, 0, this->width, this->height), QPixmap(gameoverImg));
        MyWidget::playMusic();
    }


}

void MainWindow::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_W) {
        keyWPressed = true;
    }
    if (event->key() == Qt::Key_A) {
        keyAPressed = true;
    }
    if (event->key() == Qt::Key_D) {
        keyDPressed = true;
    }
    if (event->key() == Qt::Key_F){
        keyFPressed = true;
    }
    if (event->key() == Qt::Key_R&&role->isDead()) {
        // 重新初始化游戏参数
        if (role) delete role;
        for (auto barrier : barriers) {
            delete barrier;
        }
        barriers.clear();
        role = new Role();
        monster = nullptr;
        seconds = 0;
        keyWPressed = false;
        keyAPressed = false;
        keyDPressed = false;
        keyFPressed = false;
        timer1.start();
        timer2.start();
        timer.start();
    }
    if(event->key() == Qt::Key_B&&role->isDead()){
        close();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        keyAPressed = false;
    }
    if (event->key() == Qt::Key_D) {
        keyDPressed = false;
    }
    if (event->key() == Qt::Key_F){
        keyFPressed = false;
    }

}

void MainWindow::keyProcess() {
    if (keyWPressed&&role->getJumpNum() > 0) {
        QSound::play(jump_sound);
        role->setPosY(role->getPosY() - role->getSpeedY());
        keyWPressed = false;
        //qDebug()<<role->getPosY()<<":"<<role->getJumpNum()<<":"<<keyWPressed<<"\n";
    }
    if (keyAPressed) {
        if (role->getPosX() >= role->getSpeedX()) {
            role->setPosX(role->getPosX() - role->getSpeedX());
        }
    }
    if (keyDPressed) {
        if (role->getPosX() <= width-role->getSpeedX()) {
            role->setPosX(role->getPosX() + role->getSpeedX());
        }
    }
    if(keyFPressed&&role->getCalls()>0&&!monster) {
        keyFPressed = false;
        role->setCalls(role->getCalls()-1);
        monster = new Monster(role);
    }
}

void MainWindow::writeToRecord() {
    QFile file(recordPath);
    QTextStream in(&file);
    int recordScores = 0;
    int recordSeconds = 0;

    // 打开文件
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Failed to open record file for writing!";
        return;
    }

    in >> recordScores >> recordSeconds;
    file.close();


    QTextStream out(&file);
    if (role->getScores() > recordScores) {
        recordScores = role->getScores();
        recordSeconds = seconds;
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to open record file for writing!";
            return;
        }
     out << recordScores << " " << recordSeconds;
     //qDebug()<<"Write success...\n";
     file.close();
    }
}



