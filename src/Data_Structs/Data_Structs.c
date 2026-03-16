#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Data_Structs.h"
#include "../Integrity.h"

#define Standar_size_Buffer 8

//Frame_Matrix
//The Frame_Matrix is the Matrix that will be printed into terminal. It contains each frame
//-------------------------------------------------------------------------------------------------------------------------//

//Predeclaration of needed external functions
int get_terminal_width();
int get_terminal_height();

void Create_Frame_Matrix(){
    if(Frame_Matrix.matrix != NULL){
        perror("Error: Create_Frame_Matrix Frame_Matrix has already been created\n");
        exit(EXIT_FAILURE);
    }

    int N = get_terminal_height();
    int M = get_terminal_width();

    char *c;
    c = malloc((N*M) * sizeof(char));
    if(c == NULL){
        perror("Error: Create_Frame_Matrix malloc");
        exit(EXIT_FAILURE);
    }

    Frame_Matrix.height = N;
    Frame_Matrix.width = M;
    Frame_Matrix.matrix = c;
}

void Resize_Frame_Matrix(){
    int N = get_terminal_height();
    int M = get_terminal_width();

    char *c;
    c = realloc(Frame_Matrix.matrix, (N*M) * sizeof(char));
    if(c == NULL){
        perror("Error: Resiaze_Frame_Matrix realloc");
        exit(EXIT_FAILURE);
    }

    Frame_Matrix.height = N;
    Frame_Matrix.width = M;
    Frame_Matrix.matrix = c;
}


//Buffer
//The Buffer is an array of the Objects ready to be rendericed so they can be displayed as an image
//-------------------------------------------------------------------------------------------------------------------------// 

void InicialiceBuffer(){
    if(Buffer.max_size > 0){
        perror("Error: InicialiceBuffer Buffer inicialiced more than once\n");
        exit(EXIT_FAILURE);
    }

    struct Object *O = malloc(Standar_size_Buffer * sizeof(struct Object));
    if(O == NULL){
        perror("Error: InicialiceBuffer malloc failure\n");
        exit(EXIT_FAILURE);
    }

    Buffer.size = 0;
    Buffer.max_size = Standar_size_Buffer;
    Buffer.buffer = O;
}

void insertObject_to_Buffer(struct Object *O){
    extensive_check_Object(O);

    if(Buffer.size == Buffer.max_size){
        struct Object *O = realloc(Buffer.buffer, (Buffer.max_size + Standar_size_Buffer) * sizeof(struct Object));
        if(O == NULL){
            perror("Error: insertObject_to_Buffer realloc failure\n");
            exit(EXIT_FAILURE);
        }

        Buffer.buffer = O;
        Buffer.max_size = Buffer.max_size + Standar_size_Buffer;
    }

    Buffer.buffer[Buffer.size] = *O;
    Buffer.size++;
}