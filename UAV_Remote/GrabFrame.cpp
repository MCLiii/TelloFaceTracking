//
// Created by Jim Li on 2020/10/20.
//

//This class will provide up-to-date Mat frame.

#include "GrabFrame.h"

void GrabFrame::update() {
    for (;;) {
        cap >> frame;
        good = 1;
    }
}

void GrabFrame::initialize(string name) {
    cap.open(name);
}

void GrabFrame::initialize(int code) {
    cap.open(code);
}

void GrabFrame::grab(int k) {
    for (int i = 0; i < k; i++) {
        cap.grab();
    }
}

void GrabFrame::startThread() {
    t = thread(&GrabFrame::update, this);
    t.detach();
}
