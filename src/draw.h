#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "vector.h"
#include "inir_rndrr.h"



void clear_color_buf(uint32_t color);
void draw_grid_on_buf(size_t stride, uint32_t color);
void draw_rect_on_buf(int x, int y, size_t width, size_t height, uint32_t color);
void draw_point_on_buf(int x, int y, uint32_t color);
vec2d_t project_3dto2d(vec3d_t point);