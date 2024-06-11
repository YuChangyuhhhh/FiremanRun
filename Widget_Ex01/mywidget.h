#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QDebug>
#include <QSound>
#include <QIcon>
#include <QMessageBox>
#include <QWidget>
#include<QPainter>
#include "mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
    void paintEvent(QPaintEvent*);

    void readRecord();
    static QSound* startsound;
    static void playMusic();
    static void stopMusic();
private:
    int maxScores,maxSeconds;
    MainWindow* mainwindow;
    Ui::MyWidget *ui;
};
#endif // MYWIDGET_H
