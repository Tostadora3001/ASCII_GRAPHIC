#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <math.h>


#include "Graphic.h"
#include "Integrity.h"
#include "vector3D.h"
#include "Signals_Linux.h"

//Utility functions for Point management
//-------------------------------------------------------------------------------------------------------------------------//

struct Point set_Point(struct vector3D *vec, char color){
    check_vector3D(vec);

    struct Point P;
    P.coord = *vec;

    if(color == '\n'){
        fprintf(2, "Error: new_line is not a valid color character\n");
        exit(EXIT_FAILURE);
    }
    P.color = color;

    return P;
}

struct Point move_Point_with_vector3D(struct Point *P, struct vector3D *vec){
    check_point(P);
    check_vector3D(vec);

    P->coord = vector3D_add(&P->coord, vec);
    return;
}

void change_color(struct Point *P, char color){
    P->color = color;
}

struct vector3D vector3D_A_B(struct Point *A, struct Point *B){
    check_point(A);
    check_point(B);
    
    struct vector3D diff;
    diff = vector3D_sub(A, B);

    return diff;
}

int equal_Point_exact(struct Point *A, struct Point *B){
    check_point(A);
    check_point(B);

    if(A->coord.x != B->coord.x) return 0;
    if(A->coord.y != B->coord.y) return 0;
    if(A->coord.z != B->coord.z) return 0;
    if(A->color != B->color) return 0;

    return 1;
}

int equal_Point_coord(struct Point *A, struct Point *B){
    check_point(A);
    check_point(B);
    
    if(A->coord.x != B->coord.x) return 0;
    if(A->coord.y != B->coord.y) return 0;
    if(A->coord.z != B->coord.z) return 0;

    return 1;
}

//Utility functions for Object management
//-------------------------------------------------------------------------------------------------------------------------//

struct Object Initialice_void_Object(int max_size){
    if(1 > max_size){
        perror("Error: max_size <= 0\n");
        exit(EXIT_FAILURE);
    }

    struct Object O;
    O.vector = malloc((max_size + 1) * POINT_STRUCT_SIZE);
    if(O.vector == NULL){
        perror("Error: Initialice_Object malloc\n");
        exit(EXIT_FAILURE);
    }

    O.size = 0;
    O.max_size = max_size;
    O.vector[max_size] = SENTINEL_VALUE;

    return O;
}

struct Object Initialice_load_Object(int max_size, int size, struct Point *v){
    check_arg_pointer(v);
    
    struct Object O;
    O = Initialice_void_Object(max_size);

    for(int i = 0; i < size; ++i){
        O.vector[i] = v[i];
    }

    return O;
}


void Object_max_size_modify(struct Object *O, int new_max_size){
    quick_check_Object(O);
    
    if(1 > new_max_size){
        perror("Error: max_size <= 0\n");
        exit(EXIT_FAILURE);
    }

    O->vector = realloc(O->vector, (new_max_size + 1) * POINT_STRUCT_SIZE);
    if(O->vector == NULL){
        perror("Error: Initialice_Object malloc\n");
        exit(EXIT_FAILURE);
    }

    O->max_size = new_max_size;
    if(O->max_size < O->size) O->size = O->max_size;
    O->vector[new_max_size] = SENTINEL_VALUE;

    return;
}

void add_Point_to_Object(struct Object *O, struct Point *P){
    quick_check_Object(O);
    check_point(P);

    if(O->max_size == O->size){
        perror("Error: the object is full\n");
        exit(EXIT_FAILURE);
    }
    
    O->vector[O->size - 1] = *P;

    return;
}

void del_Point_of_Object(struct Object *O, int i){
    quick_check_Object(O);

    if(i >= O->size || i < 0){
        perror("Erro: invalid index\n");
        exit(EXIT_FAILURE);
    }

    for(; i < O->size-1; ++i){
        O->vector[i] = O->vector[i+1];
    }

    --O->size;

    return;
}

void del_segment_of_Object(struct Object *O, int i, int j){
    quick_check_Object(O);
    
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
        for(int x = i; (x + (i-j) + 1) < O->size; ++x){
            O->vector[x] = O->vector[x + (i-j) + 1];
        }

        O->size = O->size - (i-j);
    }

    return;
}

void del_Object(struct Object *O){
    quick_check_Object(O);

    free(O->vector);

    O->size = 0;
    O->max_size = 0;
    O->vector = NULL;

    return;
}


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

void draw_Linux_terminal(){
    printf("\x1b[H");    //Move cursor to top left

    for(int i = 0; i < Frame_Matrix.height; ++i){
        if(write(1, Frame_Matrix.matrix, sizeof(char)*Frame_Matrix.width) < 0){ 
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

void render_frame(){
    //Objects Movement
    
}

void setFPS_ms(int ms){
    if(ms <= 0){
        perror("Error: setFPS_ms frequency too low\n");
        exit(EXIT_FAILURE);
    }

    Frame_Time_signal_configuration_Linux(ms);
}

void setFPS_hz(int hz){
    int ms = 1000 / hz;
    if(ms <= 0){
        perror("Error: setFPS_hz frequency too low\n");
        exit(EXIT_FAILURE);
    }

    Frame_Time_signal_configuration_Linux(ms);
}

//-------------------------------------------------------------------------------------------------------------------------//