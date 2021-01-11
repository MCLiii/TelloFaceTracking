//
// Created by Jim Li on 2020/9/14.
//

#include "ImageProcessing.h"

CascadeClassifier c("haarcascade_frontalface_alt2.xml");
Scalar color(183, 89, 255);
Scalar green(0, 255, 0);
vector<vector<Rect>> Que;

void ImageProcessing::faceDetection(Mat in, vector<Rect> &faces) {
    Mat gray, small_img;
    cvtColor(in, gray, COLOR_BGR2GRAY);
    resize(gray, small_img, Size(), (double) 1, (double) 1, INTER_LINEAR);
    equalizeHist(small_img, small_img);
    c.detectMultiScale(small_img, faces, 1.1, 4, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    //imageProcessing::cap->grab(3);
}

void ImageProcessing::drawRect(vector<Rect> faces, Mat &frame) {
    max = 0;
    for (int i = 0; i < faces.size(); i++) {
        Rect r = faces[i];
        if (r.width > 0)
            rectangle(frame, r, color, 2, 8, 0);
        max = r.width > faces[max].width ? i : max;
    }
    if (faces.size() != 0) {
        Mface = faces[max];
        rectangle(frame, faces[max], green, 2, 8, 0);
    } else {
        Mface.width=0;
    }
}

ImageProcessing::ImageProcessing(string addr) {
    cap.initialize(addr);
    cap.startThread();
}

void ImageProcessing::getFrame(Mat &img) {
    if (cap.ready()) {
        cap.grabFrame(frame);
        if (frame.data != NULL) {
            if (detect) {
                faceDetection(frame, faces);
                if (drect) {
                    drawRect(faces, frame);
                }
                if(grid){
                    line(frame, Point(center_x-h, 0), Point(center_x-h, 720), Scalar(255, 0, 0), 2, 1);
                    line(frame, Point(center_x+h, 0), Point(center_x+h, 720), Scalar(255, 0, 0), 2, 1);
                    line(frame, Point(0, center_y-v), Point(960,center_y-v), Scalar(255, 0, 0), 2, 1);
                    line(frame, Point(0, center_y+v), Point(960,center_y+v), Scalar(255, 0, 0), 2, 1);;
                }
            }
        }
        img = frame.clone();
    } else {
        waitKey(10);
        getFrame(img);
    }
}

ImageProcessing::ImageProcessing(int addr) {
    cap.initialize(addr);
    cap.startThread();
}

void ImageProcessing::detection(bool yes) {
    detect = yes;
}

void ImageProcessing::saveImg(string name) {
    imwrite(name, frame);
}


void ImageProcessing::getFaces(vector<Rect> &vector) {
    vector = faces;
}

void ImageProcessing::drawgird(bool _yes, int _centerX, int _centerY, int _h, int _v) {
    grid=_yes;
    center_x=_centerX;
    center_y=_centerY;
    h=_h;
    v=_v;
}


