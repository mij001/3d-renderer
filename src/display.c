#include "display.h"

size_t window_width = 0;
size_t window_height = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *rndr_texture = NULL;
uint32_t  *color_buf = NULL;

size_t renderer_init(void)
{
    // init sdl
    RNDRR_ASRT((SDL_Init(SDL_INIT_EVERYTHING) != 0), "Error: SDL initing failed!");
    SDL_DisplayMode display_info;
    SDL_GetCurrentDisplayMode(0, &display_info);
    window_height = display_info.h;
    window_width = display_info.w;

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS);

    // create sdl window
    RNDRR_ASRT((window == NULL), "Error: SDL window creation failed!");

    // create sdl renderrer
    renderer = SDL_CreateRenderer(window, -1, 0);
    RNDRR_ASRT((renderer == NULL), "Error: SDL renderer creation failed!");

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    rndr_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height);

    RNDRR_ASRT((rndr_texture == NULL), "Error: SDL texture creation failed!");

    color_buf = (uint32_t *)malloc(sizeof(uint32_t) * window_height * window_width);

    return RENDR_OK;
}
void render_color_buf()
{

    SDL_UpdateTexture(
        rndr_texture,
        NULL,
        color_buf,
        (size_t)sizeof(uint32_t) * window_width);
    SDL_RenderCopy(renderer, rndr_texture, NULL, NULL);
}

void destroy_renderer()
{
    free(color_buf);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


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