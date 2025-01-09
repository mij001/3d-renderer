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

mesh_t rndr_load_cube_mesh()
{
    mesh_t mesh;
    mesh.n_vertices = N_MESH_VERTICES;
    mesh.n_faces = N_MESH_FACES;
    // mesh.vertices = (vec3d_t *)malloc(sizeof(vec3d_t) * n_vertices);
    // mesh.vertices_tf = (vec3d_t *)malloc(sizeof(vec3d_t) * n_vertices);
    // mesh.faces = (face_t *)malloc(sizeof(face_t) * n_faces);

    // replaced by dyn arrays
    list_t vertices = list_create(sizeof(vec3d_t), 1);
    list_t vertices_tf = list_create(sizeof(vec3d_t), 1);
    list_t faces = list_create(sizeof(face_t), 1);
    list_t vertices_pj = list_create(sizeof(vec2d_t), 1);

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

    mesh.vertices = vertices;
    mesh.vertices_tf = vertices_tf;
    mesh.faces = faces;
    mesh.vertices_pj = vertices_pj;
    mesh.scale = scale;
    mesh.translate = translate;
    mesh.rotate = rotate;

    return mesh;
}

void rndr_updte_mesh(mesh_t *cube_mesh, vec3d_t camera)
{
    for (size_t i = 0; i < cube_mesh->n_vertices; i++) {
        vec3d_t pos = get_list_element(vec3d_t, cube_mesh->vertices, i);
        get_list_element(vec3d_t, cube_mesh->vertices_tf, i) = rot_x_vec(pos, cube_mesh->rotate.x);
        get_list_element(vec3d_t, cube_mesh->vertices_tf, i) = rot_y_vec(get_list_element(vec3d_t, cube_mesh->vertices_tf, i), cube_mesh->rotate.y);
        get_list_element(vec3d_t, cube_mesh->vertices_tf, i) = rot_z_vec(get_list_element(vec3d_t, cube_mesh->vertices_tf, i), cube_mesh->rotate.z);

        (get_list_element(vec3d_t, cube_mesh->vertices_tf, i)).x -= camera.x;
        (get_list_element(vec3d_t, cube_mesh->vertices_tf, i)).y -= camera.y;
        (get_list_element(vec3d_t, cube_mesh->vertices_tf, i)).z -= camera.z;
        /* TODO: cam rotation*/

        vec3d_t tf_virtex = (get_list_element(vec3d_t, cube_mesh->vertices_tf, i));
        vec2d_t p_point = project_3dto2d(tf_virtex);
        printf("%f \n", tf_virtex.x);
        get_list_element(vec2d_t, cube_mesh->vertices_pj, i) = p_point;

    }
}

void rndr_destroy_mesh(mesh_t mesh)
{
    //     free(mesh.vertices);
    //     free(mesh.vertices_tf);
    //     free(mesh.faces);

    // replaced by dyn arrays
    destroy_list(mesh.vertices_pj);
    destroy_list(mesh.faces);
    destroy_list(mesh.vertices);
    destroy_list(mesh.vertices_tf);
}

mesh_t rndr_load_obj_mesh(const char *filename)
{
    mesh_t mesh;

    FILE *fp;
    char *read_line = NULL;
    size_t n_chars2reaad = 256;

    list_t vertices = list_create(sizeof(vec3d_t), 1);
    list_t vertices_tf = list_create(sizeof(vec3d_t), 1);
    list_t faces = list_create(sizeof(face_t), 1);
    list_t vertices_pj = list_create(sizeof(vec2d_t), 1);

    fp = fopen(filename, "rw");
    assert(fp != NULL);

    mesh.n_vertices = 0;
    mesh.n_faces = 0;

    while (getline(&read_line, &n_chars2reaad, fp) != -1) {

        char type[256];
        float vertex_x;
        float vertex_y;
        float vertex_z;

        size_t face_a;
        size_t face_b;
        size_t face_c;
        if (read_line[0] == 'v') {
            sscanf(read_line, "%s %e %e %e", type, &vertex_x, &vertex_y, &vertex_z);

            vec3d_t mesh_vertices = { .x = vertex_x, .y = vertex_y,.z = vertex_z };
            push_to_list(vertices, mesh_vertices);
            push_to_list(vertices_tf, mesh_vertices);

            vec2d_t projected0 = { 0 };
            push_to_list(vertices_pj, projected0);

            mesh.n_vertices++;


            // printf("%s - %f\n", type, vertex_x);
        }
        else if (read_line[0] == 'f') {
            sscanf(read_line, "%s %lu %lu %lu", type, &face_a, &face_b, &face_c);
            face_t mesh_faces = { .a = face_a,.b = face_b,.c = face_c };
            push_to_list(faces, mesh_faces);

            mesh.n_faces++;


            // printf("%s - %d\n", type, face_a);
        }

        float scale = 0;
        vec3d_t translate = { 0 };
        vec3d_t rotate = { 0 };

        mesh.vertices = vertices;
        mesh.vertices_tf = vertices_tf;
        mesh.faces = faces;
        mesh.vertices_pj = vertices_pj;
        mesh.scale = scale;
        mesh.translate = translate;
        mesh.rotate = rotate;

    }


    if (read_line) {
        free(read_line);
    }
    return mesh;
}

vec3d_t get_face_normal(face_t face, list_t verticiess)
{
    return get_normal_vec(
        get_list_element(vec3d_t, verticiess, face.a),
        get_list_element(vec3d_t, verticiess, face.b),
        get_list_element(vec3d_t, verticiess, face.c)
    );
}