#include "camera.h"


const size_t fov_scale_factor = 15000;

vec2d_t rndr_camera_tf(vec2d_t p_point)
{
    vec2d_t camera_applied = {
        .x = (p_point.x * fov_scale_factor) + (window_width / 2),
        .y = (p_point.y * fov_scale_factor) + (window_height / 2)
    };
    return camera_applied;
}