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

vec3d_t scale_vec (vec3d_t vector, float scaler);
vec3d_t translate_vec (vec3d_t vector, vec3d_t translator);
vec3d_t rot_x_vec (vec3d_t vector, float angle);    
vec3d_t rot_y_vec (vec3d_t vector, float angle);
vec3d_t rot_z_vec (vec3d_t vector, float angle);