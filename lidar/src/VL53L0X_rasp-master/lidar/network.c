#include "network.h"


int sendLidarMessage(struct LidarMessage message)
{
    int connectSocket;
    if((connectSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_USED);
    if(inet_pton(AF_INET, SERVER_IP_ADDRESS, &serv_addr.sin_addr) <= 0)
        return -2;

    if(connect(connectSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        return -3;

    write(connectSocket, &message, sizeof(struct LidarMessage));
    close(connectSocket);
    return 0;
}
