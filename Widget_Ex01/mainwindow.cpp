#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //ui->setupUi(this);


    role = new Role();
    backPix = QPixmap(":/startBkg.png");
    groundPix = QPixmap(":/ground.png");
    bkgX = 0;
    groundX = 0;
    groundY = role->getPosY()+role->getHeight();
    width = 1400;
    height = 800;

    setWindowTitle("火柴人跑酷");
    this->setWindowIcon(QIcon(":/gameIcon.png"));
    setFixedSize(width, height);

    timer.setInterval(50);
    connect(&timer, &QTimer::timeout,  [=]() {
        update();
    });
    timer.start();
}

MainWindow::~MainWindow()
{
    if (role) delete role;
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
    painter.drawPixmap(QRect(role->getPosX(), role->getPosY(), role->getWidth(), role->getHeight()), role->figurePix[role->getFigIndex()]);


}



