#include "draw.h"

// simulate SDL_RenderClear and SDL_SetRenderDrawColor using window buffer
// 01
void clear_color_buf(uint32_t color)
{
    for (size_t row = 0; row < window_height; row++) {
        for (size_t column = 0; column < window_width; column++) {
            color_buf[(window_width * row) + column] = color;
        }
    }
}

// 02
void draw_grid_on_buf(size_t stride, uint32_t color)
{
    for (size_t row = 0; row < window_height; row += stride) {
        for (size_t column = 0; column < window_width; column += stride) {
            color_buf[(window_width * row) + column] = color;
        }
    }
}

// 03
void draw_rect_on_buf(int x, int y, size_t width, size_t height, uint32_t color)
{
    for (size_t row = x; row < x + width; row++) {
        for (size_t column = y; column < y + height; column++) {
            draw_point_on_buf(row, column, color);
        }
    }
}

// 04
void draw_point_on_buf(int x, int y, uint32_t color)
{
    /* check for screen bounds */
    if (0 <= x && x < (int)window_width && 0 <= y && y < (int)window_height) {
        color_buf[(window_width * y) + x] = color;
    }
}

void clear_z_buf(void)
{
    for (size_t i = 0; i < window_width * window_height; i++) {
        z_buf[i] = 0;
    }
}

vec2d_t project_3dto2d(vec3d_t point)
{
    vec2d_t projected = { point.x / point.z, point.y / point.z };
    return projected;
}
void draw_line_on_buf(vec2d_t p1, vec2d_t p2, uint32_t color)
{
    p1.x = (int)p1.x;
    p1.y = (int)p1.y;
    p2.x = (int)p2.x;
    p2.y = (int)p2.y;
    float x_len = fabsf(p1.x - p2.x);
    float y_len = fabsf(p1.y - p2.y);
    if (x_len == 0 && y_len == 0) {
        return;
    }

    float grad;
    float x_incr = 1;
    float y_incr = 1;
    float base_len;
    if (x_len > y_len) {
        base_len = x_len;
        grad = (p2.y - p1.y) / base_len;
        y_incr = grad;
        x_incr = (p2.x - p1.x) / base_len;
    }
    else {
        base_len = y_len;
        grad = (p2.x - p1.x) / base_len;
        x_incr = grad;
        y_incr = (p2.y - p1.y) / base_len;
    }
    float x_pos = p1.x;
    float y_pos = p1.y;
    for (float b = 0; b <= base_len; b++) {
        draw_point_on_buf(round(x_pos), round(y_pos), color);
        // draw rect as well
        // draw_rect_on_buf(round(p1.x), round(p1.y), 4, 4, color);

        x_pos += x_incr;
        y_pos += y_incr;
    }

}

void draw_triangle_on_grid(vec2d_t p1, vec2d_t p2, vec2d_t p3, uint32_t color)
{
    draw_line_on_buf(p1, p2, color);
    draw_line_on_buf(p1, p3, color);
    draw_line_on_buf(p2, p3, color);
}

void draw_face_on_grid(face_t face, list_t verticies_pj, uint32_t color)
{
    vec2d_t p_point_a = rndr_camera_tf(get_list_element(vec2d_t, verticies_pj, face.a - 1));
    vec2d_t p_point_b = rndr_camera_tf(get_list_element(vec2d_t, verticies_pj, face.b - 1));
    vec2d_t p_point_c = rndr_camera_tf(get_list_element(vec2d_t, verticies_pj, face.c - 1));

    draw_triangle_on_grid(p_point_a, p_point_b, p_point_c, color);
    //draw_filled_triangle_on_grid(p_point_a, p_point_b, p_point_c, color);
}

uint32_t shade_color(uint32_t color, float intensity)
{
    intensity = intensity < 0.15f ? 0.15f : intensity;
    intensity = intensity > 1.0f ? 1.0f : intensity;
    uint32_t r = (uint32_t)(((color >> 16) & 0xff) * intensity);
    uint32_t g = (uint32_t)(((color >> 8) & 0xff) * intensity);
    uint32_t b = (uint32_t)((color & 0xff) * intensity);
    return (color & 0xff000000) | (r << 16) | (g << 8) | b;
}

static float edge_fn(vec3d_t a, vec3d_t b, float px, float py)
{
    return (b.x - a.x) * (py - a.y) - (b.y - a.y) * (px - a.x);
}

void draw_filled_triangle_depth(vec3d_t a, vec3d_t b, vec3d_t c, uint32_t color)
{
    int min_x = (int)fminf(a.x, fminf(b.x, c.x));
    int max_x = (int)fmaxf(a.x, fmaxf(b.x, c.x)) + 1;
    int min_y = (int)fminf(a.y, fminf(b.y, c.y));
    int max_y = (int)fmaxf(a.y, fmaxf(b.y, c.y)) + 1;
    min_x = min_x < 0 ? 0 : min_x;
    min_y = min_y < 0 ? 0 : min_y;
    max_x = max_x >= (int)window_width ? (int)window_width - 1 : max_x;
    max_y = max_y >= (int)window_height ? (int)window_height - 1 : max_y;

    float area = edge_fn(a, b, c.x, c.y);
    if (area == 0) {
        return;
    }

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            float px = x + 0.5f, py = y + 0.5f;
            float w0 = edge_fn(b, c, px, py) / area;
            float w1 = edge_fn(c, a, px, py) / area;
            float w2 = edge_fn(a, b, px, py) / area;
            if (w0 < 0 || w1 < 0 || w2 < 0) {
                continue;
            }
            float inv_z = w0 / a.z + w1 / b.z + w2 / c.z;
            size_t idx = (size_t)y * window_width + x;
            if (inv_z <= z_buf[idx]) {
                continue;
            }
            z_buf[idx] = inv_z;
            color_buf[idx] = color;
        }
    }
}

static vec3d_t screen_vertex(list_t pj, list_t tf, size_t index)
{
    vec2d_t p = rndr_camera_tf(get_list_element(vec2d_t, pj, index));
    vec3d_t v = { .x = p.x, .y = p.y, .z = get_list_element(vec3d_t, tf, index).z };
    return v;
}

void draw_face_solid(face_t face, list_t verticies_pj, list_t verticies_tf, uint32_t color)
{
    vec3d_t a = screen_vertex(verticies_pj, verticies_tf, face.a - 1);
    vec3d_t b = screen_vertex(verticies_pj, verticies_tf, face.b - 1);
    vec3d_t c = screen_vertex(verticies_pj, verticies_tf, face.c - 1);

    /* anything at or behind the eye projects to nonsense */
    if (a.z <= NEAR_Z || b.z <= NEAR_Z || c.z <= NEAR_Z) {
        return;
    }
    draw_filled_triangle_depth(a, b, c, color);
}

void draw_filled_triangle_on_grid(vec2d_t p1, vec2d_t p2, vec2d_t p3, uint32_t color)
{
    vec2d_t vert_ordered[] = { p1,p2,p3 };
    for (size_t i = 0; i < 2; i++) {
        for (size_t i = 0; i < 2; i++) {
            if (vert_ordered[i].y > vert_ordered[i + 1].y) {
                vec2d_t temp = vert_ordered[i];
                vert_ordered[i] = vert_ordered[i + 1];
                vert_ordered[i + 1] = temp;
            }
        }
    }
    vec2d_t mid_vec = { .x = _calc_porpotional_x(vert_ordered[1].y, vert_ordered[0], vert_ordered[2]), .y = vert_ordered[1].y };
    _draw_flat_triangle_on_grid(mid_vec, vert_ordered[1], vert_ordered[2], color); /* top triangle */
    _draw_flat_triangle_on_grid(mid_vec, vert_ordered[1], vert_ordered[0], color); /* bttom triangle */
    // draw_triangle_on_grid(p1, p2, p3, color);
}


void _draw_flat_triangle_on_grid(vec2d_t mid, vec2d_t mid_level, vec2d_t apex, uint32_t color)
{
    draw_triangle_on_grid(mid, mid_level, apex, color);
    /* cast into ints to avoid floats blowing up */
    int mid_x = (int)((mid.x));
    int mid_level_x = (int)((mid_level.x));
    int apex_x = (int)((apex.x));
    int mid_y = (int)((mid.y));
    int mid_level_y = (int)((mid_level.y));
    int apex_y = (int)((apex.y));

    int d_height = abs(apex_y - mid_y);
    if (d_height == 0) {
        return;
    }

    float inv_slope_1 = (float)(apex_x - mid_x) / (apex_y - mid_y);
    float inv_slope_2 = (float)(apex_x - mid_level_x) / (apex_y - mid_level_y);
    float y = apex_y;
    float x_begin = apex_x;
    float x_end = apex_x;

    int sign_y = (mid_y - apex_y) / (abs(mid_y - apex_y));

    for (int i = 0; i <= d_height; i++) {
        vec2d_t v_begin = { .x = x_begin, .y = y };
        vec2d_t v_end = { .x = x_end, .y = y };

        draw_line_on_buf(v_begin, v_end, color);

        y += sign_y;
        x_begin += sign_y * inv_slope_1;
        x_end += sign_y * inv_slope_2;

    }
}

float _calc_porpotional_x(float y, vec2d_t v1, vec2d_t v2)
{
    return ((v2.x - v1.x) * (y - v1.y) / (v2.y - v1.y)) + v1.x;
}