#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QApplication>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{

    /*//QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    control.startlog();
    control.send("command");
    control.send("streamon");
    //control.takeOff();
    thread t(sendCMD);
    t.detach();
    AutoPilot autopilot(&control, &improc);
    autopilot.startThread();
    Mat frame;
    improc.detection(1);
    improc.drawrect(1);
    improc.drawgird(1,480,360,360,270);
    /*writer.open(
            "gst-launch-1.0 appsrc ! videoconvert ! x264enc noise-reduction=10000 tune=zerolatency byte-stream=true threads=4 ! mpegtsmux ! udpsink host=localhost port=9999",
            0, (double) 30, cv::Size(640, 480), true);
    if (!writer.isOpened()) {
        printf("=ERR= can't create video writer\n");
        return 0;
    }
    improc.startRec("a.avi");
    for (int i = 0 ; i < 10000; i++) {
        improc.getFrame(frame);
        circle(frame,autopilot.cpt,1,Scalar(255,0,0),4,LINE_8,0);
        imshow("feed", frame);

        waitKey(10);
    }
    control.endlog();
    //return a.exec();*/
    QApplication a(argc,argv);
    MainWindow w;
    w.show();
    return a.exec();

}
