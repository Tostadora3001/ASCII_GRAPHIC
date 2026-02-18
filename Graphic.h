#include <sys/ioctl.h>

#include "vector3D.h"

//This self-made library provides the necesary functions to generate a 2D image from a simulated 3D space
//  Valid objects for the 3D spaces are :
//      - Camera 
//      - Singular Points
//      - Geometric shapes made of the union of diferents points

//A struct of a point containing the coordinates and the character (color) that will be printed when the point is printed
struct Point{
    struct vector3D coord;
    char color;
};

//A struct of an object. An object is composed of points and the total number (size) of points (max_size is used for memory management)
struct Object{
    int size;
    int max_size;
    struct Point vector[];
};

//Utility functions for Point and Object management
//-------------------------------------------------------------------------------------------------------------------------//

//PRE  : a valid vector3D address and a char are given
//POST : a new Point is created with the vector3D as the coordinates and the char as the color
struct Point set_Point(struct vector3D *vec, char color);

//PRE  : a valid Point and vector3D addresses are given
//POST : a Point with the coordinates (coord + vector3D) modified is return
struct Point move_Point_with_vector3D(struct Point *P, struct vector3D *vec);

//PRE  : a valid Point address is given
//POST : the color of the Point is changed to the given one
void change_color(struct Point *P, char color);

//PRE  : two valid Point addresses are given
//POST : the vector3D AB is returned, being A the first point and B the second
struct vector3D vector3D_A_B(struct Point *A, struct Point *B);

//PRE  : a max_size for the object is given (it can be changed later). max_size > 0
//POST : the vector and values of Object are initialiced
struct Object Initialice_void_Object(int max_size);

//PRE  : a max_size and a valid vector of Points with its size is given. Also max_size >= vector.size && max_size > 0
//POST : the Object is initialiced with the given values.
struct Object Initialice_load_Object(int max_size, int size, struct Point v[]);

//PRE  : modify max_size of the Object
//POST : the max_size is modified and the vector too. Take in account that when reducing the max_size there is a posibility of data loss. max_size > 0
void Object_max_size_modify(struct Object *O, int new_max_size);

//PRE  : a valid Object and Point addresses are given and the Object.size < Object.max_size
//POST : the Point is added inside the Object struct
void add_Point_to_Object(struct Object *O, struct Point *P);

//PRE  : a valid Object address and a valid index of Object.vector are given
//POST : the Point ocuppying the position i in Object.vector is deleted, and the vector is adjusted, leaving free space behind
void del_Point_of_Object(struct Object *O, int i);

//PRE  : a valid Object address and two valid index of Object.vector are given. The index must validate i < j
//POST : the Points ocuppying the position i->j in Object.vector are deleted, and the vector is adjusted, leaving free space behind.
//       A segment of the Object.vector is deleted
void del_segment_of_Object(struct Object *O, int i, int j);

//PRE  : a valid Object address is given
//POST : the object is destroyed
void del_Object(struct Object *O);

//-------------------------------------------------------------------------------------------------------------------------//
//Linux Interface Terminal
//This section contains the needed code to draw the 3D simulation into the Linux terminal
//-------------------------------------------------------------------------------------------------------------------------//

//PRE  : -
//POST : Let functions get_terminal_width and get_terminal_height to function correctly
static struct winsize get_window_size();

//PRE  : -
//POST : returns the current width of the terminal
int get_terminal_width();

//PRE  : -
//POST : returns the current height of the terminal
int get_terminal_height();

//A handler for a resize event
void handle_resize(int sig);

//PRE  : -
//POST : The resize signal is configurated
void resize_signal_configuration();

//PRE  : a valid char matrix address and its dimensions (integers) are given
//POST : the given matrix is printed on terminal
void draw_Linux_terminal(char *mat, int row, int col);

//PRE  : -
//POST : The terminal is cleaned and restaured to normality
void cleanup_Linux_Terminal();

//PRE  : -
//POST : the cirsor is hided
void hide_cursor_Linux_Terminal();

//PRE  : -
//POST : The cursor is showned
void show_cursor_Linux_Terminal();

//-------------------------------------------------------------------------------------------------------------------------//

//Windows Interface Terminal
//This section contains the needed code to draw the 3D simulation into the Windows terminal
//-------------------------------------------------------------------------------------------------------------------------//

//Simulation Code
//This section contains the algorithms for a good 3D simnulation and projection into the screen
//-------------------------------------------------------------------------------------------------------------------------//

//PRE  : a vector with a pointer to all the objects to render and the number of it
//POST : the logical values and coordinates are injected into a matrix of chars ready to be printed
void render_frame();

void 

//-------------------------------------------------------------------------------------------------------------------------//