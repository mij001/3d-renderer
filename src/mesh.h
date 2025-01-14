#pragma once
#define  _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "rerr.h"
#include "vector.h"
#include "inir_rndrr.h"
#include "display.h"
#include "draw.h"
#include "face.h"
#include "array.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "matrix.h"



#define N_MESH_VERTICES 8
extern vec3d_t cube_mesh_vertices[N_MESH_VERTICES];

#define N_MESH_FACES (6 * 2) // 6 cube faces, 2 triangles per face
extern face_t cube_mesh_faces[N_MESH_FACES];

typedef struct {
    size_t n_vertices;
    size_t n_faces;
    list_t vertices; /* verticies of the mesh before linear trasforming*/
    list_t faces; /* face virticies of the mesh as indeicies of the virticies dyn array*/
    float scale; /* scaling factor of the mesh*/
    vec3d_t translate; /* translation vector of the mesh */
    vec3d_t rotate; /* rotation vector of the mesh */
    list_t vertices_tf; /* verticies of the mesh after linear trasforming*/
    list_t vertices_pj; /* projected verticies to the 2d screen */
} mesh_t;

mesh_t rndr_load_cube_mesh();
void rndr_updte_mesh(mesh_t *cube_mesh, vec3d_t camera);
void rndr_destroy_mesh(mesh_t mesh);
mesh_t rndr_load_obj_mesh(const char *filename);

vec3d_t get_face_normal(face_t face, list_t verticiess);

int rndr_is_cullable(face_t face, list_t verticiess, vec3d_t cam_pos);