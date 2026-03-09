//This is where all used data structurs such as dynamic matrix or queue are coded

#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

//Frame_Matrix
//The Frame_Matrix is the Matrix that will be printed into terminal. It contains each frame
//-------------------------------------------------------------------------------------------------------------------------//

struct Frame_Matrix{
    int height;
    int width;
    char *matrix;
};

//Declaration of the Frame_Matrix as a Global
volatile struct Frame_Matrix Frame_Matrix;

//PRE  : The terminal from where the program was started must be active
//POST : A matrix of NxM is initialiced in the heap. N and M are the diemnsions of the terminal window
void Create_Frame_Matrix();

//PRE  : The Frame_Matrix should be initialized with Create_Frame_Matrix, however it wont fail as long Frame_Matrix.matrix points into the heap
//POST : The matrix is resize in order to mainteing it coherent with terminal window size
void Resize_Frame_Matrix();


//-------------------------------------------------------------------------------------------------------------------------// 

#endif 