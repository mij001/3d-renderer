#include "vector.h"

vec3d_t scale_vec (vec3d_t vector, float scaler)
{
    vec3d_t scaled_vec =
    {
        .x=vector.x * scaler,
        .y=vector.y * scaler,
        .z=vector.z * scaler
    };
    return scaled_vec;
}

vec3d_t translate_vec (vec3d_t vector, vec3d_t translator)
{
    vec3d_t scaled_vec =
    {
        .x=vector.x + translator.x,
        .y=vector.y + translator.y,
        .z=vector.z + translator.z
    };
    return scaled_vec;
}

vec3d_t rot_x_vec (vec3d_t vector, float angle)
{
    vec3d_t rotated_vec =
    {
        .x=vector.x*cos(angle) - vector.y*sin(angle),
        .y=vector.y*cos(angle) + vector.x*sin(angle),
        .z=vector.z
    };
    return rotated_vec;
}

vec3d_t rot_y_vec (vec3d_t vector, float angle)
{
    vec3d_t rotated_vec =
    {
        .x=vector.x*cos(angle) - vector.z*sin(angle),
        .y=vector.z,
        .z=vector.z*cos(angle) + vector.x*sin(angle),
    };
    return rotated_vec;
}

vec3d_t rot_z_vec (vec3d_t vector, float angle)
{
    vec3d_t rotated_vec =
    {
        .x=vector.x,
        .y=vector.y*cos(angle) - vector.z*sin(angle),
        .z=vector.z*cos(angle) + vector.y*sin(angle)
    };
    return rotated_vec;
}