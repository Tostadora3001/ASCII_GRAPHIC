#include "Integrity.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

//Forward declarations of neede functions 
int equal_Point_exact(struct Point *A, struct Point *B);


//Utility functions for potencial errors management

void check_arg_pointer(void *pointer){
    if(pointer == NULL){
        fprintf(2, "Error: Unexpected NULL pointer in argument.\n");
        exit(EXIT_FAILURE);
    }
}

//vector3D validation functions

void check_vector3D(struct vector3D *v){
    check_arg_pointer(v);

    if(!isfinite(v->x) || !isfinite(v->y) || !isfinite(v->z)){
        fprint(2, "Error: inf or NaN value for vector3D values\n");
        exit(EXIT_FAILURE);
    }
}

void check_matrix3x3(struct matrix3x3 *M){
    check_arg_pointer(M);

    char error[64];
    for(int i = 0; i < MATRIX3x3_STRUCT_SIZE; ++i){
        if(!isfinite(M->matrix[i])){
            sprintf(error, "Error: inf or NaN value for %i element of the matrix\n", i);
            fprintf(2, error);
            exit(EXIT_FAILURE);
        }
    }
}

//Object validation functions

void check_point(struct Point *P){
    check_arg_pointer(P);

    check_vector3D(&P->coord);

    if(P->color == '\n'){
        fprintf(2, "Error: new_line is not a valid color character\n");
        exit(EXIT_FAILURE);
    }
}

void quick_check_Object(struct Object *O){
    check_arg_pointer(O);

    char error[128];
    if(O->size > O->max_size || O->max_size < 0 || O->size < 0){
        sprintf(error, "Error: incoherent values for size (%i) or max_size(%i)\n", O->size, O->max_size);
        fprintf(2, error);
    }

    //check_arg_pointer is not used here due to the incorrect message it would display
    if(O->vector == NULL){
        fprintf(2, "Error: Unexpected NULL pointer in O.vector\n");
        exit(EXIT_FAILURE);
    }
}

void extensive_check_Object(struct Object *O){
    quick_check_Object(O);
    int b = equal_Point_exact(&O->vector[O->max_size], &SENTINEL_VALUE);
    if(!b){
        fprintf(2, "Error: Sentinel Value for the Object is compromised\n");
        exit(EXIT_FAILURE);
    }

    
}
