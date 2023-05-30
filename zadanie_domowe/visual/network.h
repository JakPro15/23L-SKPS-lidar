#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>
#include <unistd.h>


struct LidarMessage
{
    uint32_t angleIndex;
    uint32_t distance;
};


int openListeningSocket(void);
int getLidarMessage(int listenSocket, struct LidarMessage *toWrite);
void stopListening(int listenSocket);

#endif
