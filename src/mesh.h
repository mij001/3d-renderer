#pragma once

#include "vector.h"
#include "list.h"

typedef struct {
    int a;
    int b;
    int c;
} face_t;

#define N_MESH_VERTICES 8
extern vec3d_t cube_mesh_vertices[N_MESH_VERTICES];

#define N_MESH_FACES (6 * 2) // 6 cube faces, 2 triangles per face
extern face_t cube_mesh_faces[N_MESH_FACES];

typedef struct {
    size_t n_vertices;
    size_t n_faces;
    list_t *vertices; /* verticies of the mesh before linear trasforming*/
    list_t *faces; /* face virticies of the mesh as indeicies of the virticies dyn array*/
    float scale; /* scaling factor of the mesh*/
    vec3d_t translate; /* translation vector of the mesh */
    vec3d_t rotate; /* rotation vector of the mesh */
    list_t *vertices_tf; /* verticies of the mesh after linear trasforming*/
    list_t *vertices_pj; /* projected verticies to the 2d screen */
} mesh_t;

mesh_t rndr_init_cube_mesh();
// void rndr_destroy_cube_mesh(mesh_t mesh);

