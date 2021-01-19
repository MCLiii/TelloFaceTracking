//
// Created by Jim Li on 2020/10/20.
//

#include "AutoPilot.h"

AutoPilot::AutoPilot(ControlSys *ctrl, ImageProcessing *improc) {
    control = ctrl;
    imageprocess = improc;

}

void AutoPilot::decision() {
    Mface=imageprocess->Mface;
    if (Mface.width == 0) {

        state[0] = 0;
        state[1] = 0;
        state[2] = 0;

    } else {

        cpt.x = Mface.x + cvRound(Mface.width / 2.0);
        cpt.y = Mface.y + cvRound(Mface.height / 2.0);

        if (Mface.width < threshL - tolerance) {
            state[1] = 1;
        } else if (Mface.width > threshL + tolerance) {
            state[1] = -1;
        } else {
            state[1] = 0;
        }

        if (!(cpt.x - Mface.width/2 < centerCoord[1] - threshHb &&
              cpt.x + Mface.width/2 > centerCoord[1] + threshHb)) {
            if (cpt.x - Mface.width/2 < centerCoord[1] - threshHb) {
                state[0] = -1;
            } else if (cpt.x + Mface.width/2 > centerCoord[1] + threshHb) {
                state[0] = 1;
            } else {
                state[0] = 0;
            }
        } else {
            state[0] = 0;
        }
        //cout<<centerCoord[0] - threshVb<<" "<<centerCoord[0] + threshVb<<'\n';
        //cout<<cpt.y<<" "<<cpt.y + Mface.height/2<<'\n';
        if (!(cpt.y - Mface.height/2 < centerCoord[0] - threshVb &&
              cpt.y + Mface.height/2 > centerCoord[0] + threshVb)) {
            if (cpt.y - Mface.height/2 < centerCoord[0] - threshVb) {
                state[2] = 1;
            } else if (cpt.y + Mface.height/2 > centerCoord[0] + threshVb) {
                state[2] = -1;
            } else {
                state[2] = 0;
            }
        } else {
            state[2] = 0;
        }

         cout << Mface.x << " " << Mface.y << " " << Mface.width << " " << Mface.height << "\n";
    }
}

void AutoPilot::sendCmd() {
    control->state(state[0], state[1], state[2]);
}

void AutoPilot::loop() {
    sendCmd();
    for (;;) {
        if (go) {
            decision();
            if(!(state[0]==prevstate[0] && state[1]==prevstate[1] && state[2]==prevstate[2])) {
                sendCmd();
                prevstate[0]=state[0];
                prevstate[1]=state[1];
                prevstate[2]=state[2];
            }
            //cout<<state[0]<<" "<<state[1]<<" "<<state[2]<<"\n";
            usleep(200000);
        } else {
            return;
        }
    }
}

void AutoPilot::startThread() {
    go = 1;
    t = thread(&AutoPilot::loop, this);
    t.detach();
}

void AutoPilot::stopThread() {
    go = 0;
    state[0] = 0;
    state[1] = 0;
    state[2] = 0;
    sendCmd();
}

/*void AutoPilot::test(int a, int b, int c) {
    if (c < threshL-tolerance) {
        state[1] = 1;
    } else if (c > threshL+tolerance) {
        state[1] = -1;
    } else {
        state[1] = 0;
    }

    if (!(a - c < centerCoord[1]-threshHb && a + c > centerCoord[1]+threshHb)) {
        if (a - c < centerCoord[1] - threshHb) {
            state[0] = 1;
        } else if (a + c > centerCoord[1] + threshHb) {
            state[0] = -1;
        } else {
            state[0] = 0;
        }
    } else {
        state[0]=0;
    }

    if(!(b - c < (centerCoord[0]-threshVb) && b + c > centerCoord[0]+threshVb)) {
        if (b - c < centerCoord[0] - threshVb) {
            state[2] = 1;
        } else if (b + c > centerCoord[0] + threshVb) {//180
            state[2] = -1;
        } else {
            state[2] = 0;
        }
    } else {
        state[2]=0;
    }
    cout<<state[0]<<" "<<state[1]<<" "<<state[2]<<"\n";
    control->state(state[0],state[1],state[2]);
}*/
