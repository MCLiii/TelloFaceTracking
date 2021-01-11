//
// Created by Jim Li on 2020/10/20.
//

#ifndef UAV_REMOTE_IMAGEPROCESSING_H
#define UAV_REMOTE_IMAGEPROCESSING_H

#include <cstdio>
#include <opencv2/opencv.hpp>
#include "GrabFrame.h"
#include  <thread>

using namespace std;
using namespace cv;

class ImageProcessing {
public:
    ImageProcessing(string addr);

    ImageProcessing(int addr);

    void getFrame(Mat &img);

    void detection(bool yes);

    void drawrect(bool yes) { drect = yes; }

    void saveImg(string name);

    void getFaces(vector<Rect> &vector);

    void drawgird(bool _yes, int _centerX, int centerY, int _h, int _v);

    Rect Mface;
private:
    void loop();

    void faceDetection(Mat in, vector<Rect> &faces);

    void drawRect(vector<Rect> faces, Mat &frame);


    Mat frame, processed;
    bool detect, drect = 1, grid;
    vector<Rect> faces;
    GrabFrame cap;
    int max, center_x, center_y, h, v;
    bool go = 0;
    thread t;
};


#endif //UAV_REMOTE_IMAGEPROCESSING_H
