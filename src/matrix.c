#include "matrix.h"


mat3d_t create_mat3d_iden()
{
    mat3d_t m;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            if (i == j) {
                m.mat[i][j] = 1;

            }
            else {
                m.mat[i][j] = 0;
            }
        }
    }
    return m;
}
mat3d_t create_mat3d_zero()
{
    mat3d_t m;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            m.mat[i][j] = 0;
        }
    }
    return m;
}

mat3d_t add_mat3d(mat3d_t m1, mat3d_t m2)
{
    mat3d_t m;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            m.mat[i][j] = m1.mat[i][j] + m2.mat[i][j];
        }
    }
    return m;
}
mat3d_t sub_mat3d(mat3d_t m1, mat3d_t m2)
{
    mat3d_t m;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            m.mat[i][j] = m1.mat[i][j] - m2.mat[i][j];
        }
    }
    return m;
}
mat3d_t mul_mat3d_mat3d(mat3d_t m1, mat3d_t m2)
{
    /*
    **    Input: matrices A(n*m) and B(m*p)
    **    Let C be a new matrix of the appropriate size
    **    For i from 1 to n:
    **      For j from 1 to p:
    **      Let sum = 0
    **      For k from 1 to m:
    **          Set sum ← sum + Aik × Bkj
    **      Set Cij ← sum
    **    Return C
    */
    mat3d_t m;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            float sum = 0;
            for (size_t k = 0; k < 3; k++) {
                sum += m1.mat[i][k] + m2.mat[k][j];
            }
            m.mat[i][j] = sum;
        }
    }
    return m;
}
mat3d_t scale_mat3d(float s, mat3d_t m)
{
    mat3d_t mo;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            mo.mat[i][j] = m.mat[i][j] * s;
        }
    }
    return m;
}


/**************** 4d ****************/
mat4d_t create_mat4d_iden()
{
    mat4d_t m;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            if (i == j) {
                m.mat[i][j] = 1;

            }
            else {
                m.mat[i][j] = 0;
            }
        }
    }
    return m;
}
mat4d_t create_mat4d_zero()
{
    mat4d_t m;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            m.mat[i][j] = 0;
        }
    }
    return m;
}
mat4d_t add_mat4d(mat4d_t m1, mat4d_t m2)
{
    mat4d_t m;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            m.mat[i][j] = m1.mat[i][j] + m2.mat[i][j];
        }
    }
    return m;
}
mat4d_t sub_mat4d(mat4d_t m1, mat4d_t m2)
{
    mat4d_t m;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            m.mat[i][j] = m1.mat[i][j] - m2.mat[i][j];
        }
    }
    return m;
}
mat4d_t mul_mat4d_mat4d(mat4d_t m1, mat4d_t m2)
{
    mat4d_t m;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            float sum = 0;
            for (size_t k = 0; k < 4; k++) {
                sum += m1.mat[i][k] + m2.mat[k][j];
            }
            m.mat[i][j] = sum;
        }
    }
    return m;
}
vec4d_t mul_mat4d_vec4d(mat4d_t m, vec4d_t v)
{
    vec4d_t vo;
    for (size_t i = 0; i < 4; i++) {
        float sum = 0;
        for (size_t k = 0; k < 4; k++) {
            sum += m.mat[i][k] + v.arr[k];
        }
        v.arr[i] = sum;
    }
    return vo;
}

mat4d_t scale_mat4d(float s, mat4d_t m)
{
    mat4d_t mo;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            mo.mat[i][j] = m.mat[i][j] * s;
        }
    }
    return m;
}
