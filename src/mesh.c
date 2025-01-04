#include "mesh.h"

vec3d_t cube_mesh_vertices[N_MESH_VERTICES] = {
    {.x = -1, .y = -1, .z = -1}, // 1
    {.x = -1, .y = 1, .z = -1},  // 2
    {.x = 1, .y = 1, .z = -1},   // 3
    {.x = 1, .y = -1, .z = -1},  // 4
    {.x = 1, .y = 1, .z = 1},    // 5
    {.x = 1, .y = -1, .z = 1},   // 6
    {.x = -1, .y = 1, .z = 1},   // 7
    {.x = -1, .y = -1, .z = 1}   // 8
};

face_t cube_mesh_faces[N_MESH_FACES] = {
    // front
    {.a = 1, .b = 2, .c = 3},
    {.a = 1, .b = 3, .c = 4},
    // right
    {.a = 4, .b = 3, .c = 5},
    {.a = 4, .b = 5, .c = 6},
    // back
    {.a = 6, .b = 5, .c = 7},
    {.a = 6, .b = 7, .c = 8},
    // left
    {.a = 8, .b = 7, .c = 2},
    {.a = 8, .b = 2, .c = 1},
    // top
    {.a = 2, .b = 7, .c = 5},
    {.a = 2, .b = 5, .c = 3},
    // bottom
    {.a = 6, .b = 8, .c = 1},
    {.a = 6, .b = 1, .c = 4}
};

mesh_t rndr_init_cube_mesh()
{
    mesh_t mesh;
    mesh.n_vertices = N_MESH_VERTICES;
    mesh.n_faces = N_MESH_FACES;
    // mesh.vertices = (vec3d_t *)malloc(sizeof(vec3d_t) * n_vertices);
    // mesh.vertices_tf = (vec3d_t *)malloc(sizeof(vec3d_t) * n_vertices);
    // mesh.faces = (face_t *)malloc(sizeof(face_t) * n_faces);

    // replaced by dyn arrays
    list_t vertices = list_create(mesh.n_vertices, 1);
    list_t vertices_tf = list_create(mesh.n_vertices, 1);
    list_t faces = list_create(mesh.n_faces, 1);
    list_t vertices_pj = list_create(mesh.n_vertices, 1);

    for (size_t i = 0; i < mesh.n_vertices; i++) {
        push_to_list(vertices, cube_mesh_vertices[i]);
        push_to_list(vertices_tf, cube_mesh_vertices[i]);

        vec2d_t projected0 = { 0 };
        push_to_list(vertices_pj, projected0);
    }
    for (size_t i = 0; i < mesh.n_faces; i++) {
        push_to_list(faces, cube_mesh_faces[i]);
    }

    float scale = 0;
    vec3d_t translate = { 0 };
    vec3d_t rotate = { 0 };

    mesh.scale = scale;
    mesh.translate = translate;
    mesh.rotate = rotate;

    return mesh;
}

// void rndr_destroy_cube_mesh(mesh_t mesh)
// {
//     //     free(mesh.vertices);
//     //     free(mesh.vertices_tf);
//     //     free(mesh.faces);

//     // replaced by dyn arrays
//     free(mesh.vertices_pj);
//     free(mesh.faces);
//     free(mesh.vertices);
//     free(mesh.vertices_tf);
// }