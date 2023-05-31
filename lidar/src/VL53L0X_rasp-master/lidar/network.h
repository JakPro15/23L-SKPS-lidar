#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


struct LidarMessage
{
    uint32_t angleIndex;
    uint32_t distance;
};

#define SERVER_IP_ADDRESS "10.42.0.1"
#define PORT_USED 12543
#define ANGLES 128
#define MIN_DISTANCE 20
#define MAX_DISTANCE 300

int sendLidarMessage(struct LidarMessage message);
