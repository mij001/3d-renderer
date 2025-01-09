#include "vector.h"

vec3d_t scale_vec(vec3d_t vector, float scaler)
{
    vec3d_t scaled_vec =
    {
        .x = vector.x * scaler,
        .y = vector.y * scaler,
        .z = vector.z * scaler
    };
    return scaled_vec;
}

vec3d_t translate_vec(vec3d_t vector, vec3d_t translator)
{
    vec3d_t scaled_vec =
    {
        .x = vector.x + translator.x,
        .y = vector.y + translator.y,
        .z = vector.z + translator.z
    };
    return scaled_vec;
}

vec3d_t rot_z_vec(vec3d_t vector, float angle)
{
    vec3d_t rotated_vec =
    {
        .x = vector.x * cos(angle) - vector.y * sin(angle),
        .y = vector.y * cos(angle) + vector.x * sin(angle),
        .z = vector.z
    };
    return rotated_vec;
}

vec3d_t rot_y_vec(vec3d_t vector, float angle)
{
    vec3d_t rotated_vec =
    {
        .x = vector.x * cos(angle) - vector.z * sin(angle),
        .y = vector.y,
        .z = vector.x * sin(angle) + vector.z * cos(angle),
    };
    return rotated_vec;
}

vec3d_t rot_x_vec(vec3d_t vector, float angle)
{
    vec3d_t rotated_vec =
    {
        .x = vector.x,
        .y = vector.y * cos(angle) - vector.z * sin(angle),
        .z = vector.z * cos(angle) + vector.y * sin(angle)
    };
    return rotated_vec;
}
float vec2d_line_distance(vec2d_t p1, vec2d_t p2)
{
    float abs_x = fabsf(p1.x - p2.x);
    float abs_y = fabsf(p1.y - p2.y);
    return sqrt(abs_x * abs_x + abs_y * abs_y);
}
float vec3d_line_distance(vec2d_t p1, vec2d_t p2)
{
    float abs_x = fabsf(p1.x - p2.x);
    float abs_y = fabsf(p1.y - p2.y);
    float abs_z = fabsf(p1.y - p2.y);
    return sqrt(abs_x * abs_x + abs_y * abs_y + abs_z * abs_z);
}

vec3d_t vec3d_add(vec3d_t v1, vec3d_t v2)
{
    vec3d_t va = {
        .x = v1.x + v2.x,
        .y = v1.y + v2.y,
        .z = v1.z + v2.z,
    };
    return va;
}

vec2d_t vec2d_add(vec2d_t v1, vec2d_t v2)
{
    vec2d_t va = {
        .x = v1.x + v2.x,
        .y = v1.y + v2.y,
    };
    return va;
}

vec3d_t vec3d_sub(vec3d_t v1, vec3d_t v2)
{
    vec3d_t va = {
        .x = v1.x - v2.x,
        .y = v1.y - v2.y,
        .z = v1.z - v2.z,
    };
    return va;
}

vec2d_t vec2d_sub(vec2d_t v1, vec2d_t v2)
{
    vec2d_t va = {
        .x = v1.x - v2.x,
        .y = v1.y - v2.y,
    };
    return va;
}

float vec3d_mag(vec3d_t v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vec2d_mag(vec2d_t v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

vec3d_t vec3d_crossp(vec3d_t v1, vec3d_t v2)
{
    vec3d_t va = {
        .x = v1.y * v2.z - v1.z * v2.y,
        .y = v1.z * v2.x - v1.x * v2.z,
        .z = v1.x * v2.y - v1.y * v2.x,
    };
    return va;
}

float vec3d_dotp(vec3d_t v1, vec3d_t v2)
{

    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


float vec2d_dotp(vec2d_t v1, vec2d_t v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

vec3d_t vec3d_normalize(vec3d_t v)
{
    float mag = vec3d_mag(v);
    vec3d_t va = {
        .x = v.x / mag,
        .y = v.y / mag,
        .z = v.z / mag,
    };
    return va;
}

vec2d_t vec2d_normalize(vec2d_t v)
{
    float mag = vec2d_mag(v);
    vec2d_t va = {
        .x = v.x / mag,
        .y = v.y / mag,
    };
    return va;
}

vec3d_t get_normal_vec(vec3d_t va, vec3d_t vb, vec3d_t vc)
{
    vec3d_t ab = vec3d_sub(vb, va);
    vec3d_t ac = vec3d_sub(vc, va);
    return vec3d_crossp(va, vc);
}