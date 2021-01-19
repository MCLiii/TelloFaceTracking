//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include <QKeyEvent>
#include <stdio.h>
#include <fstream>
#include <QDialog>

#include "opencv2/opencv.hpp"
#include "ControlSys.h"
#include "ImageProcessing.h"
#include "AutoPilot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void send();
private slots:
    void on_startBtn_pressed();
    void on_recBtn_pressed();
    void on_apBtn_pressed();
    void vslider(int val);
    void ivslider(int val);
    void ihslider(int val);
    void dslider(int  val);
private:
    Ui::MainWindow *ui;
    bool rec=0,takeoff=0;
    QGraphicsPixmapItem pixmap;
    ControlSys control;
    int state[4]{0,0,0,0};
    AutoPilot ap;
    void initSliders();
};
//#endif // MAINWINDOW_H
