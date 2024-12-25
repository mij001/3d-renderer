#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"

#define RENDR_OK 0
#define RENDR_FAILURE 1

size_t window_height = 600, window_width = 800;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
size_t end_loop = 1;
uint32_t *color_buf = NULL;

SDL_Texture *rndr_texture;

size_t renderer_init(void)
{
    // init sdl
    RNDRR_ASRT((SDL_Init(SDL_INIT_EVERYTHING) != 0), "Error: SDL initing failed!");

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

    return RENDR_OK;
}

void setup_renderer(void)
{
    SDL_DisplayMode display_info;
    SDL_GetCurrentDisplayMode(0, &display_info);
    window_height = display_info.h;
    window_width = display_info.w;

    color_buf = (uint32_t *)malloc(sizeof(uint32_t) * window_height * window_width);
    rndr_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height);
}

void handle_events(void)
{
    SDL_Event rndrr_events;
    SDL_PollEvent(&rndrr_events);

    switch (rndrr_events.type)
    {
    case SDL_QUIT:
        end_loop = 1;
        break;

    case SDL_KEYDOWN:
    {
        if (rndrr_events.key.keysym.sym == SDLK_ESCAPE)
        {
            end_loop = 1;
        }
    }
    break;

    default:
        break;
    }
}
void process_system(void) {}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

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
void draw_rect_on_buf(size_t x, size_t y, size_t width, size_t height, uint32_t color)
{
    for (size_t row = x; row < x+height; row++)
    {
        for (size_t column = y; column < y+width; column++)
        {

            color_buf[(window_width * row) + column] = color;
        }
    }
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void render_color_buf()
{
    SDL_UpdateTexture(
        rndr_texture,
        NULL,
        color_buf,
        (size_t)sizeof(uint32_t) * window_width);
    SDL_RenderCopy(renderer, rndr_texture, NULL, NULL);
}

void render_canvas(void)
{
    /*sets the color used for element drawing (like fill()) in processing*/
    SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xff);
    /*paint whole canvas with "fill" color*/
    SDL_RenderClear(renderer);
    // sdl buittin red is replaced by my color using the buffer
    clear_color_buf(0xffffff00);

    draw_grid_on_buf(10, 0xffff0000);
    draw_rect_on_buf(100, 300, 400, 500, 0xff0000ff);

    render_color_buf();
    /*like an update canvas call*/
    SDL_RenderPresent(renderer);
}

void destroy_renderer()
{
    free(color_buf);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

int main(void)
{

    end_loop = renderer_init();

    setup_renderer();

    while (!end_loop)
    {
        handle_events();
        process_system();
        render_canvas();
    }

    printf("hi mom!  \n");
    return 0;
}