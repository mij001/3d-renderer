#include "draw.h"

// simulate SDL_RenderClear and SDL_SetRenderDrawColor using window buffer
// 01
void clear_color_buf(uint32_t color)
{
    for (size_t row = 0; row < window_height; row++)
    {
        for (size_t column = 0; column < window_width; column++)
        {
            color_buf[(window_width * row) + column] = (column % 10 == 0 || row % 10 == 0) ? 0xffff0000 : color;
        }
    }
}

// 02
void draw_grid_on_buf(size_t stride, uint32_t color)
{
    for (size_t row = 0; row < window_height; row += stride)
    {
        for (size_t column = 0; column < window_width; column += stride)
        {
            color_buf[(window_width * row) + column] = color;
        }
    }
}

// 03
void draw_rect_on_buf(int x, int y, size_t width, size_t height, uint32_t color)
{
    for (size_t row = x; row < x + height; row++)
    {
        for (size_t column = y; column < y + width; column++)
        {
            draw_point_on_buf(row, column, color);
        }
    }
}

// 04
void draw_point_on_buf(int x, int y, uint32_t color)
{
    /* check for screen bounds */
    if (0 <= x && x <= (int)window_width && 0 <= y && y <= (int)window_height)
    {
        color_buf[(window_width * x) + y] = color;
    }
}