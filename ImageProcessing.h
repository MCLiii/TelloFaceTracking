//
// Created by Jim Li on 2020/10/20.
//

#ifndef UAV_REMOTE_IMAGEPROCESSING_H
#define UAV_REMOTE_IMAGEPROCESSING_H

#include <cstdio>
#include <opencv2/opencv.hpp>
#include "GrabFrame.h"
#include  <thread>
#include <unistd.h>

using namespace std;
using namespace cv;

class ImageProcessing {
public:
    ImageProcessing();

    ImageProcessing(string addr);

    ImageProcessing(int addr);

    void open(string addr);

    void open(int addr);

    void getFrame(Mat &img);

    void detection(bool yes);

    void drawrect(bool yes) { drect = yes; }

    void saveImg(string name);

    void getFaces(vector<Rect> &vector);

    void drawgird(bool _yes, int _centerX, int centerY, int _h, int _v);

    void rec(string name);

    void startRec(string name);

    void stopRec(){go=0;}

    Rect Mface;

    bool opened(){return cap.opend();}

    void close(){cap.stopThread();}
private:
    void loop();

    void faceDetection(Mat in, vector<Rect> &faces);

    void drawRect(vector<Rect> faces, Mat &frame);


    Mat frame, preProcessed;
    VideoWriter writer;
    bool detect, drect = 1, grid;
    vector<Rect> faces;
    GrabFrame cap;
    int max, center_x, center_y, h, v;
    bool go = 0;
    thread record;
};


#endif //UAV_REMOTE_IMAGEPROCESSING_H
