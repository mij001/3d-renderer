#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "vector.h"
#include "inir_rndrr.h"
#include "display.h"
#include "draw.h"

size_t end_loop = 1;
size_t mesh_size;

const size_t fov_scale_factor = 128;
vec3d_t *mesh_points = NULL;
vec2d_t *projected_points = NULL;

void setup_renderer(void)
{

    /* create mesh points 3d array */
    mesh_size = 9 * 9 * 9;
    mesh_points = (vec3d_t *)malloc(sizeof(vec3d_t) * mesh_size);
    projected_points = (vec2d_t *)malloc(sizeof(vec2d_t) * mesh_size);

    size_t point_num = 0;
    for (float x = -1; x <= 1; x += 0.25)
    {
        for (float y = -1; y <= 1; y += 0.25)
        {
            for (float z = -1; z <= 1; z += 0.25)
            {
                vec3d_t point = {.x = x, .y = y, .z = z};
                mesh_points[point_num] = point;
                //printf("%f  -  %f\n", point.x, point.y);
                point_num++;
            }
        }
    }
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
void update_system(void)
{
    for (size_t i = 0; i < mesh_size; i++)
    {
        vec3d_t point3d = mesh_points[i];
        vec2d_t p_point = project_3dto2d(point3d);
        projected_points[i] = p_point;
    }   
}

void render_canvas(void)
{
    // sdl buittin red is replaced by my color using the buffer
    clear_color_buf(0xff00ff00);

    /* scale the projection to be visible and translate to middle */
    float x_pos, y_pos;
    for (size_t i = 0; i < mesh_size; i++)
    {
        vec2d_t p_point = projected_points[i];
        x_pos = (p_point.x * fov_scale_factor) + (window_width / 2);
        y_pos = (p_point.y * fov_scale_factor) + (window_height / 2);
        //printf("%f", x_pos);
        draw_rect_on_buf(x_pos, y_pos, 2, 2, 0xff0000ff);
    }

    render_color_buf();
    /*like an update canvas call*/
    SDL_RenderPresent(renderer);
}

int main(void)
{

    end_loop = renderer_init();

    setup_renderer();

    while (!end_loop)
    {
        handle_events();
        update_system();
        render_canvas();
    }
    free(mesh_points);
    free(projected_points);
    destroy_renderer();
    printf("hi mom!  \n");
    return 0;
}