#include "visual.h"
#include "network.h"

int initialize_SDL(SDL_Window** window, SDL_Renderer** renderer, int* listenSocket)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
  	{
    	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL Initialization failed: %s\n", SDL_GetError());
    	return 1;
  	}

    *window = SDL_CreateWindow("Lidar visualisation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      	SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
  	{
    	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window creation failed: %s\n", SDL_GetError());
    	return 2;
  	}

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
  	{
    	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer creation failed: %s\n", SDL_GetError());
    	return 3;
  	}

    *listenSocket = openListeningSocket();
    if(*listenSocket < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "opening socket failed: %i\n", -*listenSocket);
        return 4;
    }

    return 0;
}


struct ExitLoopArgs
{
    SDL_bool* quit;
    int listenSocket;
};


int exit_loop(void* args)
{
    struct ExitLoopArgs* arguments = (struct ExitLoopArgs*) args;
    SDL_Event event;
    while(!(*arguments->quit))
	{
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                *arguments->quit = SDL_TRUE;
	}
    stopListening(arguments->listenSocket);
	return 0;
}

void render_loop(SDL_Renderer* renderer, int listenSocket, const SDL_bool* quit)
{
    struct LidarMessage msg;

    const struct CircleParam param = {.x = SCREEN_WIDTH / 2, .y = SCREEN_HEIGHT / 2, .r = RADIUS};
    double angles[ANGLES_COUNT];
    int64_t distances[ANGLES_COUNT];
    struct CircleParam points[ANGLES_COUNT];

    for(unsigned int i = 0; i < ANGLES_COUNT; i++)
    {
        angles[i] = -3 * M_PI_2 * (i + 0.5) / ANGLES_COUNT + M_PI_4;
        distances[i] = -1;
        points[i] = (struct CircleParam) {.x = 0, .y = 0, .r = 0};
    }

    draw_sonar(renderer, param);
    SDL_RenderPresent(renderer);

    while(!*quit)
    {
        if(getLidarMessage(listenSocket, &msg) != 0)
            break;

        if(msg.distance <= MAX_DIST)
            distances[msg.angleIndex] = msg.distance * RADIUS / MAX_DIST_RENDERED;
        else
            distances[msg.angleIndex] = -1;

        for(unsigned int i = 0; i < ANGLES_COUNT; i++)
        {
            if(distances[i] >= 0)
            {
                points[i] = (struct CircleParam) {
                    .x = SCREEN_WIDTH / 2 + (int) distances[i] * cos(angles[i]),
                    .y = SCREEN_HEIGHT / 2 + (int) distances[i] * sin(angles[i]),
                    .r = POINT_SIZE
                };
            }
        }

        draw_sonar(renderer, param);
        draw_radius(renderer, param, angles[msg.angleIndex], light_green);

        for(unsigned int i = 0; i < ANGLES_COUNT; i++)
        {
            if(distances[i] >= 0)
            {
                draw_filled_circle(renderer, points[i], light_green);
            }
        }

        SDL_RenderPresent(renderer);
    }
}


int main()
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int listenSocket;
	SDL_bool quit = SDL_FALSE;

    if(initialize_SDL(&window, &renderer, &listenSocket) != 0)
        return 1;

    struct ExitLoopArgs arguments = {.listenSocket = listenSocket, .quit = &quit};
    SDL_Thread* exit_thread = SDL_CreateThread(exit_loop, "exit_loop", (void*) &arguments);

    if(exit_thread == NULL)
    {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateThread failed: %s\n", SDL_GetError());
		return 2;
    }

	SDL_DetachThread(exit_thread);

    render_loop(renderer, listenSocket, &quit);
    close(listenSocket);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
