#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "vector.h"

typedef struct {
    vec3d_t position;
    vec3d_t rotation;
    float fov_angle;    
} camera_t;