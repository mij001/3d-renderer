#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "globals.h"

size_t renderer_init(void)
{
    // init sdl
    RNDRR_ASRT((SDL_Init(SDL_INIT_EVERYTHING) != 0), "Error: SDL initing failed!");

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

    return RENDR_OK;
}