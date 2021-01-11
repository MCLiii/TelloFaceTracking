//
// Created by Jim Li on 2020/10/20.
//

#ifndef UAV_REMOTE_CONTROLSYS_H
#define UAV_REMOTE_CONTROLSYS_H

#include <cstdio>
#include <iostream>
#include <thread>
#include <unistd.h>
#include "Networking.h"

using namespace std;

class ControlSys {
public:
    void state(int le, int fo, int up, int ro, bool safe);

    void state(int le, int fo, int up);//-1 negative, 0 no move, 1 positive
    void setVelocity(int v) { velocity = v; }

    void send(char msg[]);

    void startSecureThread();

    void emergencyStop();

    void takeOff();

    void land();

private:
    Networking packetSend;

    void trigger();

    thread t;
    int velocity = 35;
};


#endif //UAV_REMOTE_CONTROLSYS_H
