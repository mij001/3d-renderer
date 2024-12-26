#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "display.h"

size_t window_width = 0;
size_t window_height = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *rndr_texture = NULL;
uint32_t  *color_buf = NULL;

size_t renderer_init(void)
{
    // init sdl
    RNDRR_ASRT((SDL_Init(SDL_INIT_EVERYTHING) != 0), "Error: SDL initing failed!");
    SDL_DisplayMode display_info;
    SDL_GetCurrentDisplayMode(0, &display_info);
    window_height = display_info.h;
    window_width = display_info.w;

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS);

    // create sdl window
    RNDRR_ASRT((window == NULL), "Error: SDL window creation failed!");

    // create sdl renderrer
    renderer = SDL_CreateRenderer(window, -1, 0);
    RNDRR_ASRT((renderer == NULL), "Error: SDL renderer creation failed!");

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    rndr_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height);

    RNDRR_ASRT((rndr_texture == NULL), "Error: SDL texture creation failed!");

    color_buf = (uint32_t *)malloc(sizeof(uint32_t) * window_height * window_width);

    return RENDR_OK;
}