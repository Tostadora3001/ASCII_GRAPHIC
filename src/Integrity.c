#include "Integrity.h"

#include <stdlib.h>

//Utility functions for potencial errors management

void check_arg_pointer(void *pointer){
    if(pointer == NULL){
        fprintf(2, "Fatal Error: Unexpected NULL pointer in argument.\n");
        exit(EXIT_FAILURE);
    }
}