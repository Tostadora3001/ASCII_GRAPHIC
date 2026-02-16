//This own-made library provides basic 3D vector and 3x3 matrix operations and other useful utilities.

//Vectors 3D
//-------------------------------------------------------------------------------------------------------------------------//

//struct of the 3D vector
struct vector3D {
    float x;
    float y;
    float z;
};

//Assignation of the parameters of the vector with given values
//PRE  : three valid float values are given
//POST : a vector with the three values is returned. The order of assignements is :
//       arg1 = x / arg2 = y / arg3 = z
struct vector3D vector3D_parameters_assignation(float a, float b, float c);

//Addition of two 3D vectors
//PRE  : two valid 3D vectors address are given
//Post : the function returns the resulting 3D vector -> A + B = C
struct vector3D vector3D_add(struct vector3D *A, struct vector3D *B);

//Substraction of two 3D vectors
//PRE  : two valid 3D vectors address are given
//Post : the function returns the resulting 3D vector -> A - B = C
struct vector3D vector3D_sub(struct vector3D *A, struct vector3D *B);

//PRE   : two valid vector3D address are given
//POST  : an integer indicating if true or false -> 0 - false ; >0 - true
int vector3D_equal(struct vector3D *A, struct vector3D *B);

//It sets all vector's elements to 0
//PRE  : a valid 3D vector address is given 
//Post : the function sets all vector's elements to 0 -> A = 0,0,0
void vector3D_set0(struct vector3D *A);

//Scalar multiplication of a vector
//PRE  : a valid 3D vector address and float are given
//Post : the function returns the resulting 3D vector -> A = x*s , y*s , z*s
struct vector3D vector3D_escalar_multiplication(float s, struct vector3D *A);

//Magnitude of a vector
//PRE : a valid 3D vector addres is given
//POST: the function returns a float with the magnitude of the vector
float vector3D_magnitude(struct vector3D *A);

//Normalization of a vector
//PRE  : a valid 3D vector addres is given
//POST : the vector is modified seting the coresponding normalized values
//       The normalized vector is the vector with a magnitude of 1 but the same direction and orientation
struct vector3D vector3D_normalize(struct vector3D *A);


//Matrix 3x3
//-------------------------------------------------------------------------------------------------------------------------//

// A Union permits different ways to acces data in the matrix. First as a vector, second as a matrix
struct matrix3x3{
    union {
        float matrix[9];    
        float mmatrix[3][3];
    };
};

//Useful matrix3x3
// If your struct is: struct matrix { float v[9]; };

extern const struct matrix3x3 Identity;

//PRE   : three valid vector3D address are given
//POST  : a matrix3x3 is created, composed of the three vectors. So matrix = {A,B,C}
struct matrix3x3 vector3D_to_matrix3x3(struct vector3D *A, struct vector3D *B, struct vector3D *C);

//PRE   : nine valid float values are given
//POST  : a matrix with the values as parameters is returned. The assignement order is :
//        arg1 = e1 / arg2 = e2 / ... / arg9 = e9
struct matrix3x3 float_to_matrix3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i);

//PRE   : a valid float vector address is given and two integer a and b, being a the left limit of the selected
//        segment of the vector and b the right limit (a < b / a and b are indexs). The value of a and b are included.
//POST  : a matrix with the values of the vector is returned using the elemts from a to b.
//        in case that the elements between a and b is less than 9 the Identity matrix will be returned
struct matrix3x3 vector_to_matrix3x3(float v[], int a , int b);

//PRE   : two valid matrix3x3 address are given
//POST  : the function returns the sum of the matrixs
struct matrix3x3 matrix3x3_add(struct matrix3x3 *A, struct matrix3x3 *B);

//PRE   : two valid matrix3x3 address are given
//POST  : the function returns the subtraction of the matrixs
struct matrix3x3 matrix3x3_sub(struct matrix3x3 *A, struct matrix3x3 *B);

//PRE   : two valid matrix3x3 address are given
//POST  : an integer indicating if true or false -> 0 - false ; >0 - true
int matrix3x3_equal(struct matrix3x3 *A, struct matrix3x3 *B);

//It sets all matrix's elements to 0
//PRE  : a valid matrix address is given 
//Post : the function sets all matrix's elements to 0
void matrix3x3_set0(struct matrix3x3 *A);

//PRE   : a valid matrix3x3 address is given
//POST  : the function return the resulting matrix of the scalar multiplication -> {A.e1 * s , A.e2 * s , ...}
struct matrix3x3 matrix3x3_escalar_mul(float s, struct matrix3x3 *A);

//PRE   : two valid matrix3x3 address are given
//POST  ; the function returns the resulting matrix of the matrix multiplication between A and B -> AxB
struct matrix3x3 matrix3x3_matrix_mul(struct matrix3x3 *A, struct matrix3x3 *B);