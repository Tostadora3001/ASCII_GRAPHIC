#include "Graphic.h"

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