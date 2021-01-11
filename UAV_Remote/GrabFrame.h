//
// Created by Jim Li on 2020/10/20.
//

#ifndef UAV_REMOTE_GRABFRAME_H
#define UAV_REMOTE_GRABFRAME_H

#include <cstdio>
#include <opencv2/opencv.hpp>
#include <thread>

using namespace std;
using namespace cv;

class GrabFrame {
public:

    void initialize(string name);

    void initialize(int code);

    void grabFrame(Mat &img) {
        img = frame.clone();
        good = 0;
    }

    void grab(int k);

    void update();

    void startThread();

    bool ready() {
        return good;
    }

private:
    Mat frame;
    VideoCapture cap;
    thread t;
    bool good = 0;
};

#endif //UAV_REMOTE_GRABFRAME_H
