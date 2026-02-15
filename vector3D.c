#include <math.h>
#include "vector3D.h"

//Vectors 3D
//-------------------------------------------------------------------------------------------------------------------------//

struct vector3D vector3D_add(struct vector3D *A, struct vector3D *B){
    struct vector3D C;
    C.x = A->x + B->x;
    C.y = A->y + B->y;
    C.z = A->z + B->z;

    return C;
}

struct vector3D vector3D_sub(struct vector3D *A, struct vector3D *B){
    struct vector3D C;
    C.x = A->x - B->x;
    C.y = A->y - B->y;
    C.z = A->z - B->z;

    return C;
}

int vector3D_equal(struct vector3D *A, struct vector3D *B){
    int b = 1;
    if(A->x != B->x) b = 0;
    else if(A->y != B->y) b = 0;
    else if(A->z != B->z) b = 0;

    return b;
}

void vector3D_set0(struct vector3D *A){
    A->x = 0.0f;
    A->y = 0.0f;
    A->z = 0.0f;
}

struct vector3D vector3D_escalar_multiplication(float s, struct vector3D *A){
    struct vector3D C;
    C.x = A->x * s;
    C.y = A->y * s;
    C.z = A->z * s;

    return C;
}

float vector3D_magnitude(struct vector3D *A){
    float x_2 = A->x * A->x;
    float y_2 = A->y * A->y;
    float z_2 = A->z * A->z;
     
    return sqrtf(x_2 + y_2 + z_2);
}

struct vector3D vector3D_normalize(struct vector3D *A){
    struct vector3D C;
    float mag = vector3D_magnitude(A);

    C.x = A->x / mag;
    C.y = A->y / mag;
    C.z = A->z / mag;
    
    return C;
}


//Matrix 3x3
//-------------------------------------------------------------------------------------------------------------------------//

struct matrix3x3 matrix3x3_add(struct matrix3x3 *A, struct matrix3x3 *B){
    struct matrix3x3 C;
    for(int i = 0; i < 9; ++i){
        C.matrix[i] = A->matrix[i] + B->matrix[i];
    }

    return C;
}


struct matrix3x3 matrix3x3_sub(struct matrix3x3 *A, struct matrix3x3 *B){
    struct matrix3x3 C;
    for(int i = 0; i < 9; ++i){
        C.matrix[i] = A->matrix[i] - B->matrix[i];
    }

    return C;
}

int matrix3x3_equal(struct matrix3x3 *A, struct matrix3x3 *B){
    int b = 1;

    for(int i = 0; i < 9; ++i){
        if(A->matrix[i] != B->matrix[i]){
            b = 0;
            break;
        }
    }

    return b;
}

void matrix3x3_set0(struct matrix3x3 *A){
    for(int i = 0; i < 9; ++i){
        A->matrix[i] = 0;
    }
}

struct matrix3x3 matrix3x3_escalar_mul(float s, struct matrix3x3 *A){
    struct matrix3x3 C;
    for(int i = 0; i < 9; ++i){
        C.matrix[i] = A->matrix[i] * s;
    }

    return C;
}

struct matrix3x3 matrix3x3_matrix_mul(struct matrix3x3 *A, struct matrix3x3 *B){
    struct matrix3x3 C;
    for(int i = 0; i < 9; ++i){
        int aux1 = i/3;     //current row
        int aux2 = i%3;     //current column
        for(int j = 0; j < 3; ++j){
            C.matrix[i] += A->matrix[aux1 + j] * B->matrix[aux2 + j*3];
        }
    }

    return C;
}

struct matrix3x3 vector3D_to_matrix3x3(struct vector3D *A, struct vector3D *B, struct vector3D *C){
    struct matrix3x3 D;
    D.matrix[0] = A->x;
    D.matrix[1] = A->y;
    D.matrix[2] = A->z;

    D.matrix[3] = B->x;
    D.matrix[4] = B->y;
    D.matrix[5] = B->z;

    D.matrix[6] = C->x;
    D.matrix[7] = C->y;
    D.matrix[8] = C->z;

    return D;
}