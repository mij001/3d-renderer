#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "globals.h"
#include "init_stuff.h"
#include "draw.h"
#include "display.h"


void setup_renderer(void)
{
    SDL_DisplayMode display_info;
    SDL_GetCurrentDisplayMode(0, &display_info);
    window_height = display_info.h;
    window_width = display_info.w;

    color_buf = (uint32_t *)malloc(sizeof(uint32_t) * window_height * window_width);
    rndr_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height);
}

void handle_events(void)
{
    SDL_Event rndrr_events;
    SDL_PollEvent(&rndrr_events);

    switch (rndrr_events.type)
    {
    case SDL_QUIT:
        end_loop = 1;
        break;

    case SDL_KEYDOWN:
    {
        if (rndrr_events.key.keysym.sym == SDLK_ESCAPE)
        {
            end_loop = 1;
        }
    }
    break;

    default:
        break;
    }
}
void process_system(void) {}


void render_canvas(void)
{
    /*sets the color used for element drawing (like fill()) in processing*/
    SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xff);
    /*paint whole canvas with "fill" color*/
    SDL_RenderClear(renderer);
    // sdl buittin red is replaced by my color using the buffer
    clear_color_buf(0xffffff00);

    draw_grid_on_buf(10, 0xffff0000);
    draw_rect_on_buf(100, 300, 400, 500, 0xff0000ff);

    render_color_buf();
    /*like an update canvas call*/
    SDL_RenderPresent(renderer);
}


int main(void)
{

    end_loop = renderer_init();

    setup_renderer();

    while (!end_loop)
    {
        handle_events();
        process_system();
        render_canvas();
    }

    printf("hi mom!  \n");
    return 0;
}