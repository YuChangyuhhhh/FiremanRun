#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <QVector>
#include "role.h"
#include "object.h"
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
private slots:
    void updateRolePosition();
protected:
    void moveBackground();
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *) override;
private:

    bool keyWPressed;
    bool keyAPressed;
    bool keyDPressed;

    QPixmap backPix,groundPix;
    Role* role;
    QTimer timer1,timer2;
    int bkgX,groundX,groundY;
    int width,height;
    static int scores,seconds;
    QVector<Barrier*> barriers;
    int randGen,randType = -1;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
