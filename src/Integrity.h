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
//-------------------------------------------------------------------------------------------------------------------------//

//validates that the values of the vector (x,y,z) are inside R (not indeterminated values as NaN)
void check_vector3D(struct vector3D *v);

//validates that the elements of the matrix (e0,...,e8) are inside R (not indeterminated values as NaN)
void check_matrix3x3(struct matrix3x3 *M);


//Object validation functions
//-------------------------------------------------------------------------------------------------------------------------//

//validates that coord of the Point is coherent (check_vector3D) and the color is not \n
void check_point(struct Point *P);

//validetes that the size and max_size are coherent, that vector != NULL and the Sentinel Value is correct. It does not
//validate if the Points inside vector are coherent. Thus this is a quick validation
void quick_check_Object(struct Object *O);

//executes quick_check_Object and also validates that the Points inside vector are coherent. Thus is extensive
void extensive_check_Object(struct Object *O);


#endif