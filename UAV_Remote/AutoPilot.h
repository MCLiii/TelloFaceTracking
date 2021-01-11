//
// Created by Jim Li on 2020/10/20.
//

#ifndef UAV_REMOTE_AUTOPILOT_H
#define UAV_REMOTE_AUTOPILOT_H

#include <cstdio>
#include <opencv2/opencv.hpp>
#include <thread>
#include "ControlSys.h"
#include "ImageProcessing.h"

using namespace std;
using namespace cv;

class AutoPilot {
public:
    AutoPilot(ControlSys *ctrl, ImageProcessing *improc);

    void decision();

    void sendCmd();

    void loop();

    void startThread();

    void stopThread();

    void test(int a, int b, int c);

    Point cpt;
private:
    bool go;
    ControlSys *control;
    ImageProcessing *imageprocess;
    Rect Mface;
    thread t;
    vector<int> centerCoord{360, 480};
    int threshVb = 270, threshHb = 360, threshL = 200, tolerance = 80, count = 0, threshFrame = 4;
    //[0] left [1] foward [2] up
    int prevstate[3]{0,0,0}, state[3]{0, 0, 0};
};


#endif //UAV_REMOTE_AUTOPILOT_H
