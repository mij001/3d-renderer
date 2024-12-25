#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"


size_t window_height = 600, window_width = 800;
size_t end_loop = 1;
uint32_t *color_buf = NULL;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *rndr_texture;