#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include <math.h>
typedef struct
{
    float x;
    float y;
} vec2d_t;

typedef struct
{
    float x;
    float y;
    float z;

} vec3d_t;

vec3d_t scale_vec(vec3d_t vector, float scaler);
vec3d_t translate_vec(vec3d_t vector, vec3d_t translator);
vec3d_t rot_x_vec(vec3d_t vector, float angle);
vec3d_t rot_y_vec(vec3d_t vector, float angle);
vec3d_t rot_z_vec(vec3d_t vector, float angle);

float vec2d_mag(vec2d_t v);
vec2d_t vec2d_add(vec2d_t v1, vec2d_t v2);
vec2d_t vec2d_sub(vec2d_t v1, vec2d_t v2);
float vec2d_dotp(vec2d_t v1, vec2d_t v2);
vec2d_t vec2d_normalize(vec2d_t v);
float vec2d_line_distance(vec2d_t p1, vec2d_t p2);

float vec3d_mag(vec3d_t v);
vec3d_t vec3d_add(vec3d_t v1, vec3d_t v2);
vec3d_t vec3d_sub(vec3d_t v1, vec3d_t v2);
vec3d_t vec3d_crossp(vec3d_t v1, vec3d_t v2);
float vec3d_dotp(vec3d_t v1, vec3d_t v2);
vec3d_t vec3d_normalize(vec3d_t v);
float vec3d_line_distance(vec2d_t p1, vec2d_t p2);

vec3d_t get_normal_vec(vec3d_t va, vec3d_t vb, vec3d_t vc);