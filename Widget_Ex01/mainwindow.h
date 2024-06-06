#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "role.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void maxScoreFile();
    int getWidth(){return width;}
    int getHeight(){return height;}
protected:
    void moveBackground();
    void paintEvent(QPaintEvent *);
private:
    QPixmap backPix,groundPix;
    Role* role;
    QTimer timer;
    int bkgX,groundX,groundY;
    int width,height;
    static int scores,seconds;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
