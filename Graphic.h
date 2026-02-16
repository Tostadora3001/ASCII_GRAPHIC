#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

#include "vector3D.h"

//This self-made library provides the necesary functions to generate a 2D image from a simulated 3D space
//  Valid objects for the 3D spaces are :
//      - Camera 
//      - Singular Points
//      - Geometric shapes made of the union of diferents points


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



//-------------------------------------------------------------------------------------------------------------------------//