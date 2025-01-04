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