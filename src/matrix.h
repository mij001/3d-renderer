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
#include "camera.h"

typedef struct
{
    float mat[4][4];
}
mat4d_t;

typedef struct
{
    float mat[3][3];
}
mat3d_t;

mat3d_t create_mat3d_iden();
mat3d_t create_mat3d_zero();
mat3d_t add_mat3d(mat3d_t m1, mat3d_t m2);
mat3d_t sub_mat3d(mat3d_t m1, mat3d_t m2);
mat3d_t mul_mat3d_mat3d(mat3d_t m1, mat3d_t m2);
mat3d_t scale_mat3d(float s, mat3d_t m);

mat4d_t create_mat4d_iden();
mat4d_t create_mat4d_zero();
mat4d_t add_mat4d(mat4d_t m1, mat4d_t m2);
mat4d_t sub_mat4d(mat4d_t m1, mat4d_t m2);
mat4d_t mul_mat4d_mat4d(mat4d_t m1, mat4d_t m2);
vec4d_t mul_mat4d_vec4d(mat4d_t m, vec4d_t v);
mat4d_t scale_mat4d(float s, mat4d_t m);