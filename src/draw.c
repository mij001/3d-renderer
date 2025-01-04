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
    if (0 <= x && x <= (int)window_width && 0 <= y && y <= (int)window_height) {
        color_buf[(window_width * y) + x] = color;
    }
}

vec2d_t project_3dto2d(vec3d_t point)
{
    vec2d_t projected = { point.x / point.z, point.y / point.z };
    return projected;
}
void draw_line_on_buf(vec2d_t p1, vec2d_t p2, uint32_t color)
{
    float x_len = fabsf(p1.x - p2.x);
    float y_len = fabsf(p1.y - p2.y);
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
    vec2d_t p1 = get_list_element(vec2d_t, verticies_pj, face.a);
    vec2d_t p2 = get_list_element(vec2d_t, verticies_pj, face.b);
    vec2d_t p3 = get_list_element(vec2d_t, verticies_pj, face.c);

    draw_triangle_on_grid(p1, p2, p3, color);
}