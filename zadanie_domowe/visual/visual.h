#define __USE_MISC

#include <SDL2/SDL.h>
#include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 820
#define MIN(x,y) (x) < (y) ? (x) : (y)
#define MAX(x,y) (x) > (y) ? (x) : (y)
#define RADIUS ((unsigned int) floor(MIN(SCREEN_WIDTH,SCREEN_HEIGHT) * 0.45))
#define POINT_SIZE (MAX((unsigned int) floor(MIN(SCREEN_WIDTH,SCREEN_HEIGHT) / 273),1))
#define CIRCLE_COUNT 4
#define ANGLES_COUNT 16
#define MAX_DIST_RENDERED 200
#define MAX_DIST (MAX_DIST_RENDERED - POINT_SIZE)


struct CircleParam
{
    unsigned int x;
    unsigned int y;
    unsigned int r;
};

extern const SDL_Color dark_green;
extern const SDL_Color light_green;
int initialize_SDL(SDL_Window** window, SDL_Renderer** renderer, int* listenSocket);
int exit_loop(void* quit);
void render_loop(SDL_Renderer* renderer, int listenSocket, const SDL_bool* quit);
void draw_filled_circle(SDL_Renderer* renderer, const struct CircleParam param, const SDL_Color color);
void draw_circle(SDL_Renderer* renderer, const struct CircleParam param, const SDL_Color color, const SDL_bool full);
void draw_sonar(SDL_Renderer* renderer, const struct CircleParam param);
void draw_radius(SDL_Renderer* renderer, const struct CircleParam param, const double angle, const SDL_Color color);
