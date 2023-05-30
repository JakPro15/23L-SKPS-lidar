#include "visual.h"

const SDL_Color dark_green = {.r = 1, .g = 69, .b = 28, .a = 255};
const SDL_Color light_green = {.r = 33, .g = 243, .b = 116, .a = 255};

void draw_filled_circle(SDL_Renderer* renderer, const struct CircleParam param, const SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (unsigned int w = 0; w < param.r * 2; w++)
    {
        for (unsigned int h = 0; h < param.r * 2; h++)
        {
            int dx = param.r - w;
            int dy = param.r - h;
            if ((unsigned int)(dx * dx + dy * dy) <= (param.r * param.r))
            {
                SDL_RenderDrawPoint(renderer, param.x + dx, param.y + dy);
            }
        }
    }
}

void draw_circle(SDL_Renderer* renderer, const struct CircleParam param, const SDL_Color color, const SDL_bool full)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int t1 = param.r / 16;
    int x = param.r;
    int y = 0;
    int t2;

    while(x >= y)
    {
        SDL_RenderDrawPoint(renderer, param.x + x, param.y + y);
        SDL_RenderDrawPoint(renderer, param.x - x, param.y + y);
        SDL_RenderDrawPoint(renderer, param.x - x, param.y - y);
        SDL_RenderDrawPoint(renderer, param.x - y, param.y - x);
        SDL_RenderDrawPoint(renderer, param.x + y, param.y - x);
        SDL_RenderDrawPoint(renderer, param.x + x, param.y - y);

        if(full)
        {
            SDL_RenderDrawPoint(renderer, param.x + y, param.y + x);
            SDL_RenderDrawPoint(renderer, param.x - y, param.y + x);
        }

        y++;
        t1 += y;
        t2 = t1 - x;
        if(t2 >= 0)
        {
            t1 = t2;
            x--;
        }
    }
}

void draw_sonar(SDL_Renderer* renderer, const struct CircleParam param)
{
    draw_filled_circle(renderer, param, dark_green);

    for(uint8_t i = 0; i < CIRCLE_COUNT; i++)
    {
        struct CircleParam param_cpy = param;
        SDL_bool full = SDL_FALSE;
        param_cpy.r = RADIUS * (i + 1) / CIRCLE_COUNT;
        if(i == CIRCLE_COUNT - 1)
            full = SDL_TRUE;

        draw_circle(renderer, param_cpy, light_green, full);
    }

    SDL_RenderDrawLine(renderer, param.x, param.y, param.x + RADIUS * M_SQRT1_2, param.y + RADIUS * M_SQRT1_2);
    SDL_RenderDrawLine(renderer, param.x, param.y, param.x - RADIUS * M_SQRT1_2, param.y + RADIUS * M_SQRT1_2);
}

void draw_radius(SDL_Renderer* renderer, const struct CircleParam param, const double angle, const SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_RenderDrawLine(
        renderer,
        param.x, param.y,
        param.x + (int) (param.r * cos(angle)),
        param.y + (int) (param.r * sin(angle))
    );
}
