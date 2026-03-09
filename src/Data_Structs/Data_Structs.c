#include <stdio.h>
#include <stdlib.h>

#include "Data_Structs.h"

//Predeclaration of needed external functions
int get_terminal_width();
int get_terminal_height();

//PRE  : The terminal from where the program was started must be active
//POST : A matrix of NxM is initialiced in the heap. N and M are the diemnsions of the terminal window-
//       Frame_Matrix will contein the size and the pointer to the matrix
void Create_Frame_Matrix(){
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

//PRE  : The Frame_Matrix should be initialized with Create_Frame_Matrix, however it wont fail as long Frame_Matrix.matrix points into the heap
//POST : The matrix is resize in order to mainteing it coherent with terminal window size
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