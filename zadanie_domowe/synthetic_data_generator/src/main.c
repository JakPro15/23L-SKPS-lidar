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

#define SERVER_IP_ADDRESS "10.0.2.2"
#define PORT_USED 12543
#define ANGLES 128
#define MIN_DISTANCE 20
#define MAX_DISTANCE 300


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


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "usage: synthetic_data_generator [1|2|3|help]\n");
        return 1;
    }
    if(strcmp(argv[1], "help") == 0)
    {
        printf("The first argument to the program should be a number, 1, 2 or 3, "
               "selecting a distance generation mode.\n"
               "1 - randomly generated\n"
               "2 - increasing until maximum, then looping back to minimum\n"
               "3 - decreasing until minimum, then looping back to maximum\n");
        return 0;
    }

    int generation_mode = atoi(argv[1]);
    srand(time(NULL));
    int angleIndex = 0, distance;
    bool angleIncreasing = true;

    switch(generation_mode)
    {
    case 1:
        distance = rand() % (MAX_DISTANCE - MIN_DISTANCE) + MIN_DISTANCE;
        break;
    case 2:
        distance = MIN_DISTANCE;
        break;
    case 3:
        distance = MAX_DISTANCE;
        break;
    default:
        fprintf(stderr, "usage: synthetic_data_generator [1|2|3|help]\n");
        return 1;
    }
    while(1)
    {
        struct LidarMessage message = {.angleIndex = angleIndex, .distance = distance};
        if(sendLidarMessage(message) != 0)
        {
            fprintf(stderr, "Failed to send synthetic data message\n");
            return 1;
        }
        if(angleIncreasing)
        {
            if(angleIndex == ANGLES - 1)
            {
                --angleIndex;
                angleIncreasing = false;
            }
            else
                ++angleIndex;
        }
        else
        {
            if(angleIndex == 0)
            {
                ++angleIndex;
                angleIncreasing = true;
            }
            else
                --angleIndex;
        }
        switch(generation_mode)
        {
        case 1:
            distance = rand() % (MAX_DISTANCE - MIN_DISTANCE) + MIN_DISTANCE;
            break;
        case 2:
            ++distance;
            if(distance >= MAX_DISTANCE)
                distance = MIN_DISTANCE;
            break;
        case 3:
            --distance;
            if(distance <= MIN_DISTANCE)
                distance = MAX_DISTANCE;
        }
        usleep(100000);
    }
    return 0;
}
