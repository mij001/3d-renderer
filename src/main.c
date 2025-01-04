#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "vector.h"
#include "inir_rndrr.h"
#include "display.h"
#include "mesh.h"
#include "draw.h"
#include "array.h"
#include "list.h"
#include "face.h"

const int FPS = 60;
const int FPS_MS = 1000 / FPS;
size_t tickes_in_prev_frame = 0;

size_t end_loop = 1;

const size_t fov_scale_factor = 700;


mesh_t cube_mesh_g;
// list_t mesh_points_dyn;
// list_t mesh_points_tf_dyn;
// list_t projected_points_dyn;


vec3d_t camera_pos_g;
float rot_angle = 0;

void setup_renderer(void)
{
    vec3d_t camera_pos = {
        .x = 0,
        .y = 0,
        .z = -5
    };

    camera_pos_g = camera_pos;

    cube_mesh_g = rndr_init_cube_mesh();
    // mesh_points_dyn = list_create(sizeof(vec3d_t), 1);
    // mesh_points_tf_dyn = list_create(sizeof(vec3d_t), 1);
    // projected_points_dyn = list_create(sizeof(vec3d_t), 1);
    // for (size_t i = 0; i < N_MESH_VERTICES; i++) {
    //     vec3d_t point = cube_mesh_vertices[i];
    //     push_to_list(mesh_points_dyn, point);
    //     vec2d_t p_point = { .x = point.x, .y = point.y };
    //     push_to_list(mesh_points_tf_dyn, point);
    //     push_to_list(projected_points_dyn, p_point);
    // }
}

void handle_events(void)
{
    SDL_Event rndrr_events;
    SDL_PollEvent(&rndrr_events);

    switch (rndrr_events.type) {
    case SDL_QUIT:
        end_loop = 1;
        break;

    case SDL_KEYDOWN:
    {
        if (rndrr_events.key.keysym.sym == SDLK_ESCAPE) {
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
    if (0 <= sleep_time && sleep_time <= FPS_MS) {
        SDL_Delay(sleep_time);
    }
    tickes_in_prev_frame = SDL_GetTicks();
    /////////////////////////////////

    for (size_t i = 0; i < N_MESH_VERTICES; i++) {
        /* point scaling, translation and rotations */
        /* point scaling */
        rndr_updte_mesh(&cube_mesh_g, camera_pos_g);
        // get_list_element(vec3d_t, mesh_points_tf_dyn, i) = rot_x_vec(get_list_element(vec3d_t, mesh_points_dyn, i), rot_angle);
        // get_list_element(vec3d_t, mesh_points_tf_dyn, i) = rot_y_vec(get_list_element(vec3d_t, mesh_points_tf_dyn, i), rot_angle);
        // get_list_element(vec3d_t, mesh_points_tf_dyn, i) = rot_z_vec(get_list_element(vec3d_t, mesh_points_tf_dyn, i), rot_angle);

        cube_mesh_g.rotate.x += 0.001;
        cube_mesh_g.rotate.y += 0.001;
        cube_mesh_g.rotate.z += 0.001;
        // printf("%f\n", rot_angle);

        /* point transation */
        /* point rotation */

        /* code the camera position translstion & rotation */
        /* cam translation */
        // (get_list_element(vec3d_t, mesh_points_tf_dyn, i)).x -= camera_pos_g.x;
        // (get_list_element(vec3d_t, mesh_points_tf_dyn, i)).y -= camera_pos_g.y;
        // (get_list_element(vec3d_t, mesh_points_tf_dyn, i)).z -= camera_pos_g.z;

        // /* TODO: cam rotation*/
        // vec3d_t tf_virtex = (get_list_element(vec3d_t, mesh_points_tf_dyn, i));
        // vec2d_t p_point = project_3dto2d(tf_virtex);
        // printf("%f \n", tf_virtex.x);
        // get_list_element(vec2d_t, projected_points_dyn, i) = p_point;
    }
}

void render_canvas(void)
{
    // sdl buittin red is replaced by my color using the buffer
    clear_color_buf(0xff000000);

    /* scale the projection to be visible and translate to middle */
    float x_pos, y_pos;
    for (size_t i = 0; i < cube_mesh_g.n_vertices; i++) {
        // vec2d_t p_point = projected_points[i];
        vec2d_t p_point = get_list_element(vec2d_t, cube_mesh_g.vertices_pj/*projected_points_dyn*/, i);

        x_pos = (p_point.x * fov_scale_factor) + (window_width / 2);
        y_pos = (p_point.y * fov_scale_factor) + (window_height / 2);
        draw_rect_on_buf(x_pos, y_pos, 4, 4, 0xff00ff00);
        // printf("%f \n", x_pos);

        // face_t face2draw = get_list_element(face_t, cube_mesh_g.faces, i);
        // draw_face_on_grid(face2draw, cube_mesh_g.vertices_pj, 0xff00ff00);
        // /////////////////////////////////////
    }

    vec2d_t p1 = { .x = 100, .y = 500 };
    vec2d_t p2 = { .x = 650, .y = 600 };
    vec2d_t p3 = { .x = 456, .y = 600 };
    /////////////////////////////////////
    /////////////////////////////////////
    draw_point_on_buf(p1.x, p1.y, 0xff00ff00);
    draw_rect_on_buf(p1.x, p1.y, 4, 4, 0xff00ff00);

    draw_point_on_buf(p2.x, p2.y, 0xff00ff00);
    draw_rect_on_buf(p2.x, p2.y, 4, 4, 0xff00ff00);

    draw_point_on_buf(p3.x, p3.y, 0xff00ff00);
    draw_rect_on_buf(p3.x, p3.y, 4, 4, 0xff00ff00);

    // draw_line_on_buf(p1, p2, 0xff00ff00);
    // draw_line_on_buf(p1, p3, 0xff00ff00);
    // draw_line_on_buf(p2, p3, 0xff00ff00);

    draw_triangle_on_grid(p1, p2, p3, 0xff00ff00);

    render_color_buf();
    /*like an update canvas call*/
    SDL_RenderPresent(renderer);
}

int main(void)
{
    end_loop = renderer_init();

    setup_renderer();

    while (!end_loop) {
        handle_events();
        update_system();
        render_canvas();
    }
    // free(mesh_points);
    // destroy_list(projected_points_dyn);
    // destroy_list(mesh_points_tf_dyn);
    // destroy_list(mesh_points_dyn);
    rndr_destroy_cube_mesh(cube_mesh_g);
    destroy_renderer();
    printf("hi mom!  \n");
    return 0;
}