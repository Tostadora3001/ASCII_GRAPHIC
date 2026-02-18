#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include "Graphic.h"

//Utility functions for Point and Object management
//-------------------------------------------------------------------------------------------------------------------------//

struct Point set_Point(struct vector3D *vec, char color){
    struct Point P;
    P.coord = vec;
    P.color = color;

    return P;
}

struct Point move_Point_with_vector3D(struct Point *P, struct vector3D *vec){
    P->coord = vector3D_add(&P->coord, *vec);
    return;
}

void change_color(struct Point *P, char color){
    P->color = color;
}

struct vector3D vector3D_A_B(struct Point *A, struct Point *B){
    struct vector3D diff;
    diff = vector3D_sub(*A, *B);

    return diff;
}

struct Object Initialice_Object(int max_size){
    if(1 > max_size){
        perror("Error: max_size <= 0\n");
        exit(EXIT_FAILURE);
    }

    struct Object O;
    O.vector = malloc(max_size);
    if(O.vector == NULL){
        perror("Error: Initialice_Object malloc\n");
        exit(EXIT_FAILURE);
    }

    O.size = 0;
    O.max_size = max_size;
    return O;
}

void Object_max_size_modify(struct Object *O, int new_max_size){
    if(1 > new_max_size){
        perror("Error: max_size <= 0\n");
        exit(EXIT_FAILURE);
    }

    O->vector = realloc(O->vector, new_max_size);
    if(O->vector == NULL){
        perror("Error: Initialice_Object malloc\n");
        exit(EXIT_FAILURE);
    }

    O->max_size = new_max_size;
    if(O->max_size < O->size) O->size = O->max_size;

    return;
}

void add_Point_to_Object(struct Object *O, struct Point *P){
    if(O->max_size == O->size){
        perror("Error: the object is full\n");
        exit(EXIT_FAILURE);
    }
    
    O->vector[O->size - 1] = P;
}

void del_Point_of_Object(struct Object *O, int i){
    if(i >= O->size || i < 0){
        perror("Erro: invalid index\n");
        exit(EXIT_FAILURE);
    }

    for(; i < size-1; ++i){
        O->vector[i] = O->vector[i+1];
    }

    --size;
}

void del_segment_of_Object(struct Object *O, int i, int j){
    if(i >= O->size || i < 0){
        perror("Erro: invalid index i\n");
        exit(EXIT_FAILURE);
    }

    if(j >= O->size || j < 0){
        perror("Erro: invalid index j\n");
        exit(EXIT_FAILURE);
    }

    if(i > j){
        perror("Error: i must be smaller than j (i < j)\n");
        exit(EXIT_FAILURE);
    }

    if(j == O->size - 1) O->size = i + 1;
    else{
        for(x = i; (x + (i-j) + 1) < O->size; ++x){
            O->vector[x] = O->vector[x + (i-j) + 1];
        }

        O->size = O->size - (i-j);
    }
}

void del_Object(struct Object *O);


//-------------------------------------------------------------------------------------------------------------------------//
//Linux Interface Terminal
//This section contains the needed code to draw the 3D simulation into the Linux terminal
//-------------------------------------------------------------------------------------------------------------------------//

static struct winsize get_window_size(){
    struct winsize w;
    // We use STDOUT_FILENO to query the dimensions of the terminal output
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        // Fallback or error handling: return 0s if it fails
        w.ws_row = 0;
        w.ws_col = 0;
    }
    return w;
}

// Function to get current terminal width (Columns)
int get_terminal_width(){
    struct winsize w = get_window_size();
    return w.ws_col;
}

// Function to get current terminal height (Rows)
int get_terminal_height(){
    struct winsize w = get_window_size();
    return w.ws_row;
}


void handle_resize(int sig){
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0){
        perror("Error : ioctl syscall error"); 
        exit(EXIT_FAILURE);
    }
    //printf("\nResize detected! New Size: %d x %d\n", w.ws_col, w.ws_row);
}

void resize_signal_configuration(){
    if(signal(SIGWINCH, handle_resize) == SIG_ERR){ 
        perror("Error: resize siganl configuration"); 
        exit(EXIT_FAILURE);
    }
    return 0;
}

void draw_Linux_terminal(char *mat, int row, int col){
    printf("\x1b[H")    //Move cursor to top left

    for(int i = 0; i < row; ++i){
        if(fwrite(1, mat, sizeof(char)*col) < 0){ 
            perror("Error: draw_Linux_terminal write(mat)"); 
            exit(EXIT_FAILURE);
        }
        if(putc('\n', 1) < 0){
            perror("Error: draw_Linux_terminal putchar"); 
            exit(EXIT_FAILURE);
        }
    }
}

void cleanup_Linux_Terminal() {
    show_cursor_Linux_Terminal();
    printf("\x1b[0m");
}

void hide_cursor_Linux_Terminal() {
    printf("\x1b[?25l");
}

void show_cursor_Linux_Terminal() {
    printf("\x1b[?25h");
}

//-------------------------------------------------------------------------------------------------------------------------//

//Windows Interface Terminal
//This section contains the needed code to draw the 3D simulation into the Windows terminal
//-------------------------------------------------------------------------------------------------------------------------//

//Simulation Code
//This section contains the algorithms for a good 3D simnulation and projection into the screen
//-------------------------------------------------------------------------------------------------------------------------//



//-------------------------------------------------------------------------------------------------------------------------//