#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "network.h"

#define PORT_USED 12543


signed int openListeningSocket(void)
{
    signed int listenSocket;
    if((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    signed int true_value = 1;
    if(setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR,
                  &true_value, sizeof(int)) < 0)
        return -2;

    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT_USED);

    if(bind(listenSocket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        return -3;

    if(listen(listenSocket, 10) < 0)
        return -4;

    return listenSocket;
}


signed int getLidarMessage(signed int listenSocket, struct LidarMessage* toWrite)
{
    char buffer[4 * sizeof(struct LidarMessage)];

    signed int connectSocket;
    if((connectSocket = accept(listenSocket, (struct sockaddr*) NULL, NULL)) < 0)
    {
        if(errno == EINVAL)
            return -1;
        else
            return -2;
    }

    unsigned totalBytesRead = 0;
    while(totalBytesRead < sizeof(struct LidarMessage))
    {
        signed int bytesRead = read(connectSocket, buffer + totalBytesRead, sizeof(buffer) - totalBytesRead);
        if(bytesRead < 0)
            return -3;
        totalBytesRead += bytesRead;
    }
    memcpy(toWrite, buffer, sizeof(struct LidarMessage));
    close(connectSocket);
    return 0;
}


void stopListening(int listenSocket)
{
    shutdown(listenSocket, SHUT_RDWR);
}
