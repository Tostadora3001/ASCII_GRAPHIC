#ifndef STRUCT_VECTOR3D_H
#define STRUCT_VECTOR3D_H

//vector3D
//struct of the 3D vector

struct vector3D {
    float x;
    float y;
    float z;
};

//Matrix 3x3
// A Union permits different ways to acces data in the matrix. First as a vector, second as a matrix

struct matrix3x3{
    union {
        float matrix[9];    
        float mmatrix[3][3];
    };
};

#endif