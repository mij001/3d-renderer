#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "globals.h"
#include "rerr.h"
#include "init_stuff.h"

extern size_t window_height;
extern size_t window_width;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *rndr_texture;

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

    return RENDR_OK;
}
void render_color_buf()
{

    SDL_UpdateTexture(
        rndr_texture,
        NULL,
        color_buf,
        (size_t)sizeof(uint32_t) * window_width);
    SDL_RenderCopy(renderer, rndr_texture, NULL, NULL);
}

void destroy_renderer()
{
    free(color_buf);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}