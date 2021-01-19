#include "mainwindow.h"
#include "./ui_mainwindow.h"

ImageProcessing video;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));
    initSliders();
    ui->graphicsView->scene()->addItem(&pixmap);
    control.startlog();
    control.send("command");
    control.send("streamon");
}

void MainWindow::initSliders(){
    ui->vSlide->setMinimum(1);
    ui->vSlide->setMaximum(100);
    ui->vSlide->setValue(35);
    ui->dSlide->setMaximum(-100);
    ui->dSlide->setMinimum(-400);
    ui->dSlide->setValue(-200);
    connect(ui->vSlide, SIGNAL(valueChanged(int)), this, SLOT(vslider(int)));
    connect(ui->dSlide, SIGNAL(valueChanged(int)), this, SLOT(dslider(int)));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(video.opened()) {
        QMessageBox::warning(this,"Warning","Stop the video before closing the application!");
        event->ignore();
    } else if(rec) {
        QMessageBox::warning(this,"Warning","Stop the recording before closing the application");
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::on_startBtn_pressed() {
    using namespace cv;

    if(video.opened()) {
        ui->startBtn->setText("Start");
        video.close();
        return;
    }

    bool isCamera;
    video.open("udp://@:11111");

    ui->startBtn->setText("Stop");

    Mat frame;
    while(video.opened()) {
        video.getFrame(frame);
        if(!frame.empty()) {
            QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
            pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
        }
        qApp->processEvents();
    }
    video.close();
    ui->startBtn->setText("Start");
}

void MainWindow::on_recBtn_pressed() {
    ui->recBtn->setText("wtf");
    int recNum=0;
    ifstream fin("log.txt", ios::in);
    fin>>recNum;
    cout<<recNum;
    if (video.opened()){
        if(rec) {
           ofstream fout("log.txt",ios::out);
           fout<<(recNum+1);
           video.stopRec();
           fout.close();
           ui->recBtn->setText("Start Rec");
           rec=0;
       } else {
           rec=1;
           video.startRec(to_string(recNum)+".avi");
           ui->recBtn->setText("Recording");
       }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_W) {
        state[1]=1;
    } else if(event->key() == Qt::Key_A) {
        state[0]=-1;
    } else if(event->key() == Qt::Key_S) {
        state[1]=-1;
    } else if(event->key() == Qt::Key_D) {
        state[0]=1;
    } else if(event->key() == Qt::Key_I) {
        state[2]=1;
    } else if(event->key() == Qt::Key_J) {
        state[3]=-1;
    } else if(event->key() == Qt::Key_K) {
        state[2]=-1;
    } else if(event->key() == Qt::Key_L) {
        state[3]=1;
    } else if(event->key() == Qt::Key_T) {
        if(!takeoff){
            control.takeOff();
            takeoff=1;
        } else {
            control.land();
            takeoff=0;
        }
    }
    if(ap.started()){
        on_apBtn_pressed();
        QMessageBox::warning(this,"Warning","Autopilot disengaged!");
    }
    send();
}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_W) {
        state[1]=0;
    } else if(event->key() == Qt::Key_A) {
        state[0]=0;
    } else if(event->key() == Qt::Key_S) {
        state[1]=0;
    } else if(event->key() == Qt::Key_D) {
        state[0]=0;
    } else if(event->key() == Qt::Key_I) {
        state[2]=0;
    } else if(event->key() == Qt::Key_J) {
        state[3]=0;
    } else if(event->key() == Qt::Key_K) {
        state[2]=0;
    } else if(event->key() == Qt::Key_L) {
        state[3]=0;
    } else if(event->key() == Qt::Key_F) {
        control.send("flip l");
    }
    send();
}

void MainWindow::send() {
    control.state(state[0]*control.getVelocity(),
                  state[1]*control.getVelocity(),
                  state[2]*control.getVelocity(),
                  state[3]*control.getVelocity(),0);
    ui->label->setText(QString::number(state[0])+" "+QString::number(state[1])+" "+QString::number(state[2])+" "+QString::number(state[3]));
}

void MainWindow::on_apBtn_pressed() {
    if(!ap.started()){
        if (state[0]!=0 || state[1]!=0 || state[2]!=0 || state[3]!=0){
            QMessageBox::warning(this,"Warning","Release ALL keys before engaging autopilot!");
        } else {
            video.drawgird(1,480,360,360,270);
            video.detection(1);
            video.drawrect(1);
            ap.init(&control,&video);
            ap.startThread();
            ui->apBtn->setText("AutoPilot Engaged");
        }

    } else {
        video.drawgird(0,480,360,360,270);
        video.detection(0);
        video.drawrect(0);
        ap.stopThread();
        ui->apBtn->setText("Engage AutoPilot");
    }
}

void MainWindow::vslider(int val) {
    ui->label->setText(QString::number(val));
    control.setVelocity(val);
}

void MainWindow::ivslider(int val) {

}

void MainWindow::ihslider(int val) {

}

void MainWindow::dslider(int val) {
    ui->label->setText(QString::number(val));
    ap.threshL=-val;
}
