#ifndef STRUCT_GRAPHIC_H
#define STRUCT_GRAPHIC_H

#include "struct_vector3D.h"

//A struct of a point containing the coordinates and the character (color) that will be printed when the point is printed
struct Point{
    struct vector3D coord;
    char color;
};

//A struct of an object. An object is composed of points and the total number (size) of points (max_size is used for memory management)
struct Object{
    int size;
    int max_size;
    struct Point *vector;
};

//A struct of a camera. A Camera is a special point, needed for the graphic calculation. It is composed of a point and a direction, both being a vector3D
struct Camera{
    struct vector3D coord;
    struct vector3D dir;
};

#endif