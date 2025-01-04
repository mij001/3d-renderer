#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "vector.h"
#include "inir_rndrr.h"
#include "display.h"
#include "draw.h"
#include "mesh.h"
#include "array.h"
#include "list.h"
#include "face.h"

void clear_color_buf(uint32_t color);
void draw_grid_on_buf(size_t stride, uint32_t color);
void draw_rect_on_buf(int x, int y, size_t width, size_t height, uint32_t color);
void draw_point_on_buf(int x, int y, uint32_t color);
void draw_line_on_buf(vec2d_t p1, vec2d_t p2, uint32_t color);
void draw_triangle_on_grid(vec2d_t p1, vec2d_t p2, vec2d_t p3, uint32_t color);

void draw_face_on_grid(face_t face, list_t verticies_pj, uint32_t color);

vec2d_t project_3dto2d(vec3d_t point);