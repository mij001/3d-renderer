#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "globals.h"


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