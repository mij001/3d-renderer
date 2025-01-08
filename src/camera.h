#pragma once

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "vector.h"
#include "inir_rndrr.h"
#include "display.h"
#include "mesh.h"
#include "draw.h"
#include "array.h"
#include "list.h"
#include "face.h"

typedef struct {
    vec3d_t position;
    vec3d_t rotation;
    float fov_angle;
} camera_t;

vec2d_t rndr_camera_tf(vec2d_t p_point);