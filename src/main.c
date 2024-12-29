#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "vector.h"
#include "inir_rndrr.h"
#include "display.h"
#include "draw.h"
#include "mesh.h"
#include "array.h"

const int FPS = 30;
const int FPS_MS = 1000 / FPS;
size_t tickes_in_prev_frame = 0;

size_t end_loop = 1;

const size_t fov_scale_factor = 700;

// vec3d_t *mesh_points = NULL;
vec3d_t *mesh_points_dyn = NULL;

// vec3d_t *mesh_points_tf = NULL;
vec3d_t *mesh_points_tf_dyn = NULL;

// vec2d_t *projected_points = NULL;
vec2d_t *projected_points_dyn = NULL;

vec3d_t camera_pos_g;
float rot_angle = 0;

void setup_renderer(void)
{
    vec3d_t camera_pos = {
        .x = 0,
        .y = 0,
        .z = -5};

    camera_pos_g = camera_pos;
    // mesh_points = (vec3d_t *)malloc(sizeof(vec3d_t) * N_MESH_VERTICES);
    // mesh_points_dyn = (vec3d_t *)malloc(sizeof(vec3d_t) * N_MESH_VERTICES);
    // mesh_points_tf = (vec3d_t *)malloc(sizeof(vec3d_t) * N_MESH_VERTICES);
    // mesh_points_tf_dyn = (vec3d_t *)malloc(sizeof(vec3d_t) * N_MESH_VERTICES);

    array_hold(mesh_points_dyn, N_MESH_VERTICES, sizeof(vec3d_t));
    array_hold(mesh_points_tf_dyn, N_MESH_VERTICES, sizeof(vec3d_t));
    array_hold(projected_points_dyn, N_MESH_VERTICES, sizeof(vec2d_t));


    // projected_points = (vec2d_t *)malloc(sizeof(vec2d_t) * N_MESH_VERTICES);
    //projected_points_dyn = (vec2d_t *)malloc(sizeof(vec2d_t) * N_MESH_VERTICES);

    for (size_t i = 0; i < N_MESH_VERTICES; i++)
    {

        vec3d_t point = mesh_vertices[i];
        // mesh_points[i] = point;
        array_push(mesh_points_dyn, point);

        // mesh_points_tf[i] = point;
        array_push(mesh_points_tf_dyn, point);
        // printf("%f  -  %f\n", point.x, point.y);
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

    /* add delay to updating loop to get a constant fps */
    int sleep_time = FPS_MS - (SDL_GetTicks() - tickes_in_prev_frame);
    // sleep the prodcess
    if (0 <= sleep_time && sleep_time <= FPS_MS)
    {
        SDL_Delay(sleep_time);
    }
    tickes_in_prev_frame = SDL_GetTicks();
    /////////////////////////////////
    projected_points_dyn = NULL;

    for (size_t i = 0; i < N_MESH_VERTICES; i++)
    {
        /* point scaling, translation and rotations */
        /* point scaling */
        //  mesh_points_tf[i] = rot_x_vec(mesh_points[i], rot_angle);
        //  mesh_points_tf[i] = rot_x_vec(mesh_points_dyn[i], rot_angle);
        //  mesh_points_tf[i] = rot_y_vec(mesh_points_tf[i], rot_angle);
        //  mesh_points_tf[i] = rot_z_vec(mesh_points_tf[i], rot_angle);
        //mesh_points_tf_dyn[i] = rot_x_vec(mesh_points_dyn[i], rot_angle);
        mesh_points_tf_dyn[i] = rot_x_vec(mesh_points_dyn[i], rot_angle);
        mesh_points_tf_dyn[i] = rot_y_vec(mesh_points_tf_dyn[i], rot_angle);
        mesh_points_tf_dyn[i] = rot_z_vec(mesh_points_tf_dyn[i], rot_angle);

        rot_angle += 0.0001;
        //printf("%f\n", rot_angle);

        /* point transation */
        /* point rotation */

        /* code the camera position translstion & rotation */
        /* cam translation */
        // mesh_points_tf[i].x -= camera_pos_g.x;
        // mesh_points_tf[i].y -= camera_pos_g.y;
        // mesh_points_tf[i].z -= camera_pos_g.z;
        mesh_points_tf_dyn[i].x -= camera_pos_g.x;
        mesh_points_tf_dyn[i].y -= camera_pos_g.y;
        mesh_points_tf_dyn[i].z -= camera_pos_g.z;

        /* TODO: cam rotation*/
        // vec2d_t p_point = project_3dto2d(mesh_points_tf[i]);
        vec3d_t tf_virtex = mesh_points_tf_dyn[i];
        vec2d_t p_point = project_3dto2d(tf_virtex);
        printf("%f \n", tf_virtex.x);
        // projected_points[i] = p_point;
        // projected_points_dyn[i] = p_point;
        array_push(projected_points_dyn, p_point);
    }
}

void render_canvas(void)
{
    // sdl buittin red is replaced by my color using the buffer
    clear_color_buf(0xff000000);

    /* scale the projection to be visible and translate to middle */
    float x_pos, y_pos;
    for (size_t i = 0; i < N_MESH_VERTICES; i++)
    {
        // vec2d_t p_point = projected_points[i];
        vec2d_t p_point = projected_points_dyn[i];

        x_pos = (p_point.x * fov_scale_factor) + (window_width / 2);
        y_pos = (p_point.y * fov_scale_factor) + (window_height / 2);
        //printf("%f \n", x_pos);
        draw_rect_on_buf(x_pos, y_pos, 4, 4, 0xff00ff00);
    }

    array_free(projected_points_dyn);
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
    // free(mesh_points);
    free(mesh_points_dyn);
    free(mesh_points_tf_dyn);
    destroy_renderer();
    printf("hi mom!  \n");
    return 0;
}