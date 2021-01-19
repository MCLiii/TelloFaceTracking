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
#include <QTextStream>

using namespace std;
using namespace cv;

class AutoPilot {
public:
    AutoPilot(ControlSys *ctrl, ImageProcessing *improc);

    AutoPilot(){}

    void init(ControlSys *ctrl, ImageProcessing *improc){control=ctrl;imageprocess=improc;}

    void decision();

    void sendCmd();

    void loop();

    void startThread();

    void stopThread();

    void test(int a, int b, int c);

    Point cpt;

    bool started(){return go;}

    int threshVb = 270, threshHb = 360, threshL = 180, tolerance = 80, count = 0;
private:
    ofstream fout;
    bool go;
    ControlSys *control;
    ImageProcessing *imageprocess;
    Rect Mface;
    thread t;
    vector<int> centerCoord{360, 480};
    //[0] left [1] foward [2] up
    int prevstate[3]{0,0,0}, state[3]{0, 0, 0};

};


#endif //UAV_REMOTE_AUTOPILOT_H
