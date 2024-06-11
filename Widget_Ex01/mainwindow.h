#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFile>
#include <QTimer>
#include <QTime>
#include <QSound>
#include <QMessageBox>
#include <QKeyEvent>
#include <QVector>
#include "role.h"
#include "object.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MyWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void maxScoreFile();
    int getWidth(){return width;}
    int getHeight(){return height;}
    void writeToRecord();
    void initialize();
private slots:
    void keyProcess();
protected:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *) override;

private:

    bool keyWPressed;
    bool keyAPressed;
    bool keyDPressed;
    bool keyFPressed;


    QPixmap backPix,groundPix;
    Role* role;
    Monster* monster;
    QTimer timer1,timer2,timer;
    int bkgX,groundX,groundY;
    int width,height;
    int seconds;
    QVector<Object*> barriers;
    int randGen,randType = -1;
    bool gameover;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
