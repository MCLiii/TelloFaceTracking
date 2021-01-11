//
// Created by Jim Li on 2020/10/20.
//

#ifndef UAV_REMOTE_NETWORKING_H
#define UAV_REMOTE_NETWORKING_H


#include <cstdio>
#include <cstring>
#include <string>
#include <cerrno>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <array>

using namespace std;
typedef unsigned char byte;

class Networking {
public:
    Networking();
    Networking(const char* IP, int Port);

    void udpSend(char data[]);

private:
    int DEST_PORT=8889;

    const char *DSET_IP_ADDRESS = "192.168.10.1";
};


#endif //UAV_REMOTE_NETWORKING_H
