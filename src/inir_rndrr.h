#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "display.h"

extern size_t window_height;
extern size_t window_width;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *rndr_texture;
extern uint32_t  *color_buf;

size_t renderer_init(void);