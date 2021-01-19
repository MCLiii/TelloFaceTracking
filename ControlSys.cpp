//
// Created by Jim Li on 2020/10/20.
//

#include "ControlSys.h"


void ControlSys::state(int fo, int le, int up, int ro, bool safe) {
    log<<fo<<" "<<" "<<le<<" "<<ro<<" "<<safe<<"\n";
    cout<<fo<<" "<<" "<<le<<" "<<ro<<" "<<safe<<"\n";
    string msg = "rc " + to_string(fo) + " " + to_string(le) + " " + to_string(up) + " " + to_string(ro);
    //cout<<msg<<"\n";
    packetSend.udpSend(&msg[0]);
    if (safe)
        startSecureThread();
}

void ControlSys::emergencyStop() {
    state(0, 0, 0, 0, 0);
}

void ControlSys::trigger() {
    sleep(3);
    emergencyStop();
}

void ControlSys::startSecureThread() {
    t = thread(&ControlSys::trigger, this);
    t.detach();
}

void ControlSys::send(char msg[]) {
    log<<msg<<"\n";
    packetSend.udpSend(msg);
}

void ControlSys::takeOff() {
    send("takeoff");
}

void ControlSys::land() {
    send("land");
}

void ControlSys::state(int fo, int le, int up) {
    state(fo * velocity, le * velocity, up * velocity, 0, 0);
}


