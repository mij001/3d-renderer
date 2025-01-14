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
                sum += m1.mat[i][k] * m2.mat[k][j];
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
    return mo;
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
                sum += m1.mat[i][k] * m2.mat[k][j];
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
            sum += m.mat[i][k] * v.arr[k];
        }
        vo.arr[i] = sum;
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
    return mo;
}

mat4d_t create_scale_mat4d(float x, float y, float z)
{
    mat4d_t m = create_mat4d_iden();
    m.mat[0][0] = x;
    m.mat[1][1] = y;
    m.mat[2][2] = z;
    return m;
}

mat4d_t create_transl_mat4d(float x, float y, float z)
{
    mat4d_t m = create_mat4d_iden();
    m.mat[3][0] = x;
    m.mat[3][1] = y;
    m.mat[3][2] = z;
    return m;
}

mat4d_t create_rot_mat4d(float x, float y, float z)
{
    mat4d_t rx = create_mat4d_iden();
    rx.mat[1][1] = cos(x);
    rx.mat[2][2] = cos(x);
    rx.mat[1][2] = sin(x);
    rx.mat[2][1] = -sin(x);

    mat4d_t ry = create_mat4d_iden();
    ry.mat[0][0] = cos(y);
    ry.mat[2][2] = cos(y);
    ry.mat[2][0] = sin(y);
    ry.mat[0][2] = -sin(y);

    mat4d_t rz = create_mat4d_iden();
    rz.mat[0][0] = cos(z);
    rz.mat[1][1] = cos(z);
    rz.mat[1][0] = sin(z);
    rz.mat[0][1] = -sin(z);
    mat4d_t m = mul_mat4d_mat4d(rx, mul_mat4d_mat4d(ry, rz));
    return m;
}

mat4d_t create_mat4d_perspective(float aspect, float fov, float zfar, float znear)
{
    mat4d_t m = create_mat4d_zero();
    m.mat[0][0] = aspect * (1 / tan(fov / 2));
    m.mat[1][1] = 1 / tan(fov / 2);
    m.mat[2][2] = zfar / (zfar - znear);
    m.mat[2][3] = (-zfar * znear) / (zfar - znear);
    m.mat[3][2] = 1;
    return m;
}