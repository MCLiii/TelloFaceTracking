//
// Created by Jim Li on 2020/10/20.
//

#include "Networking.h"

#include <utility>

Networking::Networking() {}

void Networking::udpSend(char send_buf[]) {
    /* socket文件描述符 */
    int sock_fd;

    /* 建立udp socket */
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        exit(1);
    }

    /* 设置address */
    struct sockaddr_in addr_serv;
    int len;
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(DSET_IP_ADDRESS);
    addr_serv.sin_port = htons(DEST_PORT);
    len = sizeof(addr_serv);


    int send_num;
    int recv_num;
    char recv_buf[20];

    log<<"client send:"<<" "<< send_buf<<"\n";

    send_num = sendto(sock_fd, send_buf, strlen(send_buf), 0, (struct sockaddr *) &addr_serv, len);

    if (send_num < 0) {
        perror("sendto error:");
        exit(1);
    }

    /*recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_serv, (socklen_t *)&len);

    if(recv_num < 0)
    {
        perror("recvfrom error:");
        exit(1);
    }

    recv_buf[recv_num] = '\0';
    printf("client receive %d bytes: %s\n", recv_num, recv_buf);

    close(sock_fd);
}*/;
}

Networking::Networking(const char* IP, int Port) {
    DEST_PORT=Port;
    DSET_IP_ADDRESS= IP;
}
