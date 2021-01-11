#include <cstdio>
#include <opencv2/opencv.hpp>
#include <thread>
#include "ControlSys.h"
#include "ImageProcessing.h"
#include "AutoPilot.h"

using namespace cv;
using namespace std;

ControlSys control;

void sendCMD() {
    string a;
    for (;;) {
        cin >> a;
        if (a == "l") {
            control.land();
            break;
        }
    }
}

int main() {
    control.send("command");
    control.send("streamon");
    control.takeOff();
    thread t(sendCMD);
    t.detach();
    ImageProcessing improc("udp://@:11111");
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
    }*/
    for (;;) {
        improc.getFrame(frame);
        circle(frame,autopilot.cpt,1,Scalar(255,0,0),4,LINE_8,0);
        imshow("feed", frame);
        waitKey(10);
    }
}

/*int main(){
    control.send("command");
    control.send("streamon");
    control.takeOff();
    for(int i=0;;i++){
        /*improc.getFrame(frame);
        imshow("feed",frame);
        improc.getFaces(faces);
        waitKey(10);
        int a, b , c, d;
        cin>>a>>b>>c>>d;
        control.state(a,b,c,d,0);
    }
}*/
