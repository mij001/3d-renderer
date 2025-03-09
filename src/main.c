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
#include "camera.h"
#include "matrix.h"


#define TEST_FILL_TRIANGLEn

const int FPS = 60;
const int FPS_MS = 1000 / FPS;
size_t tickes_in_prev_frame = 0;
size_t frame_cnt = 0;

size_t fov_scale_factor = 700;

size_t end_loop = 1;

mesh_t obj_mesh_g;

vec3d_t camera_pos_g;
vec3d_t light_dir_g = { .x = 0, .y = 0, .z = 1 };
int render_mode_g = 0; /* 0 solid, 1 wire, 2 both */
int paused_g = 0;
float rot_angle = 0;

/* normalise the model to a unit radius so any obj fits the window */
void fit_mesh_to_view(mesh_t *mesh)
{
    float max_r = 0;
    for (size_t i = 0; i < mesh->n_vertices; i++) {
        float r = vec3d_mag(get_list_element(vec3d_t, mesh->vertices, i));
        max_r = r > max_r ? r : max_r;
    }
    if (max_r <= 0) {
        return;
    }
    mesh->scale.x = mesh->scale.y = mesh->scale.z = 1.0f / max_r;
    fov_scale_factor = (5 * window_height) / 3;
}

void setup_renderer(const char *obj_path)
{
    vec3d_t camera_pos = {
        .x = 0,
        .y = 0,
        .z = 0
    };

    camera_pos_g = camera_pos;
    if (obj_path == NULL) {
        obj_mesh_g = rndr_load_cube_mesh();
        return;
    }
    obj_mesh_g = rndr_load_obj_mesh(obj_path);
    obj_mesh_g.rotate.z = 3.14;
    fit_mesh_to_view(&obj_mesh_g);
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
        switch (rndrr_events.key.keysym.sym) {
        case SDLK_ESCAPE: end_loop = 1; break;
        case SDLK_TAB: render_mode_g = (render_mode_g + 1) % 3; break;
        case SDLK_w: camera_pos_g.z += 0.1; break;
        case SDLK_s: camera_pos_g.z -= 0.1; break;
        case SDLK_a: camera_pos_g.x -= 0.1; break;
        case SDLK_d: camera_pos_g.x += 0.1; break;
        case SDLK_SPACE: paused_g = !paused_g; break;
        case SDLK_EQUALS: fov_scale_factor += fov_scale_factor / 10; break;
        case SDLK_MINUS: fov_scale_factor -= fov_scale_factor / 10; break;
        case SDLK_LEFT: obj_mesh_g.rotate.y -= 0.05; break;
        case SDLK_RIGHT: obj_mesh_g.rotate.y += 0.05; break;
        case SDLK_UP: obj_mesh_g.rotate.x -= 0.05; break;
        case SDLK_DOWN: obj_mesh_g.rotate.x += 0.05; break;
        default: break;
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

    if (!paused_g) {
        obj_mesh_g.rotate.x += 0.001;
        obj_mesh_g.rotate.y += 0.001;
        obj_mesh_g.rotate.z += 0.001;
    }
    rndr_updte_mesh(&obj_mesh_g, camera_pos_g);
}

void report_fps(void)
{
    static size_t last_ms = 0;
    frame_cnt++;
    size_t now = SDL_GetTicks();
    if (now - last_ms < 1000) {
        return;
    }
    printf("%.1f fps\n", frame_cnt * 1000.0 / (now - last_ms));
    last_ms = now;
    frame_cnt = 0;
}

void render_canvas(void)
{
    // sdl buittin red is replaced by my color using the buffer
    report_fps();
    clear_color_buf(0xff000000);
    clear_z_buf();
    for (size_t i = 0; i < obj_mesh_g.n_faces; i++) {
        // vec2d_t p_point = projected_points[i];
        face_t face = get_list_element(face_t, obj_mesh_g.faces, i);
        if (1 != rndr_is_cullable(face, obj_mesh_g.vertices_tf, camera_pos_g)) {
            vec3d_t normal = vec3d_normalize(get_face_normal(face, obj_mesh_g.vertices_tf));
            float intensity = -vec3d_dotp(normal, light_dir_g);
            if (render_mode_g != 1) {
                draw_face_solid(face, obj_mesh_g.vertices_pj, obj_mesh_g.vertices_tf,
                    shade_color(0xff00ff00, intensity));
            }
            if (render_mode_g != 0) {
                draw_face_on_grid(face, obj_mesh_g.vertices_pj, 0xff303030);
            }
        }
    }



#ifdef TEST_FILL_TRIANGLE
    vec2d_t p1 = { .x = 700, .y = 600 };
    vec2d_t p2 = { .x = 650.9, .y = 600 };
    vec2d_t p3 = { .x = 456, .y = 754 };
    vec2d_t p4 = { .x = 1000, .y = 754 };
    draw_triangle_on_grid(p3, p4, p1, 0xffff0000);
    _draw_flat_triangle_on_grid(p3, p4, p1, 0xff00ff00);
    // draw_filled_triangle_on_grid(p1, p2, p4, 0xffff0000);

    vec2d_t f1_p1 = { .x = 821.561707, .y = 357.745483 };
    vec2d_t f1_p2 = { .x = 629.245911, .y = 619.015442 };
    vec2d_t f1_p3 = { .x = 887.785767, .y = 703.334412 };
    vec2d_t f2_p1 = { .x = 821.561707, .y = 357.745483 };
    vec2d_t f2_p2 = { .x = 887.785767, .y = 703.334412 };
    vec2d_t f2_p3 = { .x = 1088.306274, .y = 512.892700 };;
    vec2d_t f3_p1 = { .x = 781.239929, .y = 230.340332 };
    vec2d_t f3_p2 = { .x = 648.041382, .y = 436.603943 };
    vec2d_t f3_p3 = { .x = 629.245911, .y = 619.015442 };
    vec2d_t f4_p1 = { .x = 781.239929, .y = 230.340332 };
    vec2d_t f4_p2 = { .x = 629.245911, .y = 619.015442 };
    vec2d_t f4_p3 = { .x = 821.561707, .y = 357.745483 };
    vec2d_t f5_p1 = { .x = 981.110107, .y = 362.471008 };
    vec2d_t f5_p2 = { .x = 781.239929, .y = 230.340332 };
    vec2d_t f5_p3 = { .x = 821.561707, .y = 357.745483 };
    vec2d_t f6_p1 = { .x = 981.110107, .y = 362.471008 };
    vec2d_t f6_p2 = { .x = 821.561707, .y = 357.745483 };
    vec2d_t f6_p3 = { .x = 1088.306274, .y = 512.892700 };;

    draw_filled_triangle_on_grid(f1_p1, f1_p2, f1_p3, 0xff00ff00);
    draw_filled_triangle_on_grid(f2_p1, f2_p2, f2_p3, 0xff00ff00);
    draw_filled_triangle_on_grid(f3_p1, f3_p2, f3_p3, 0xff00ff00);
    draw_filled_triangle_on_grid(f4_p1, f4_p2, f4_p3, 0xff00ff00);
    draw_filled_triangle_on_grid(f5_p1, f5_p2, f5_p3, 0xff00ff00);
    draw_filled_triangle_on_grid(f6_p1, f6_p2, f6_p3, 0xff00ff00);

    // draw_triangle_on_grid(f1_p1, f1_p2, f1_p3, 0xff00ff00);
    // draw_triangle_on_grid(f2_p1, f2_p2, f2_p3, 0xffff0000);
    // draw_triangle_on_grid(f3_p1, f3_p2, f3_p3, 0xff00ff00);
    // draw_triangle_on_grid(f4_p1, f4_p2, f4_p3, 0xfff00f00);
    // draw_triangle_on_grid(f5_p1, f5_p2, f5_p3, 0xff0000ff);
    // draw_triangle_on_grid(f6_p1, f6_p2, f6_p3, 0xff00f00f);


#endif


    render_color_buf();
    /*like an update canvas call*/
    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    end_loop = renderer_init();

    setup_renderer(argc > 1 ? argv[1] : NULL);

    while (!end_loop) {
        handle_events();
        update_system();
        render_canvas();
    }
    rndr_destroy_mesh(obj_mesh_g);
    destroy_renderer();
    printf("hi mom!  \n");
    return 0;
}