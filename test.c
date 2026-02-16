#include <stdio.h>
#include <string.h>

#include "Graphic.h"

struct vector3D aux, aux2;

void debuger(int i){
    printf("%f %f %f\n" , aux.x, aux.y, aux.z);
    printf("%f %f %f\n" , aux2.x, aux2.y, aux2.z);

    if(vector3D_equal(&aux, &aux2)){
        printf("Test %i : Son iguales\n", i);
    }
    else printf("Test %i : No son iguales\n", i);
}

int main(){

    vector3D_set0(&aux);
    vector3D_set0(&aux2);

    debuger(1);
    
    aux = vector3D_parameters_assignation(1.0f, 2.0f, 3.0f);
    aux2 = vector3D_parameters_assignation(1.0f, 2.0f, 3.0f);
    aux = vector3D_add(&aux, &aux2);

    debuger(2);

    aux2 = vector3D_sub(&aux2, &aux);
    debuger(3);

    aux = vector3D_add(&aux, &aux2);
    aux2 = vector3D_escalar_multiplication(-1.0f, &aux2);

    debuger(4);

    printf("\n%f\n\n", vector3D_magnitude(&aux));

    aux2 = vector3D_normalize(&aux2);

    debuger(5);

    return 0;
}