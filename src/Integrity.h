//This header includes integrity validation functions, in order to garantee a correct execution.
//The next functions are designed to work with vector3D.h and Graphic.h, however fell free to customize 
//this code as your will

#ifndef INTEGRITY_H
#define INTEGRITY_H

#include "Structs/struct_graphic.h"
#include "Structs/struct_vector3D.h"

//Utility functions for potencial errors management

//Validates that the given pointer is not a NULL
void check_arg_pointer(void *pointer);

//vector3D validation functions
void check_vector3D(struct vector3D);

//Object validation functions

#endif