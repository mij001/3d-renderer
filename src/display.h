#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"

extern size_t window_height;
extern size_t window_width;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *rndr_texture;
extern uint32_t  *color_buf;

void clear_color_buf(uint32_t color);
void draw_grid_on_buf(size_t stride, uint32_t color);
void draw_rect_on_buf(int x, int y, size_t width, size_t height, uint32_t color);
void draw_point_on_buf(int x, int y, uint32_t color);
size_t renderer_init(void);
void render_color_buf();
void destroy_renderer();