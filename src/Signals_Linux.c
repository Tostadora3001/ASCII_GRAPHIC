#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "Signals_Linux.h"
#include "Data_Structs/Data_Structs.h"

//Pre declaration of external used dunctions and usefull variables
void cleanup_Linux_Terminal();
void Resize_Frame_Matrix();

extern volatile struct Frame_Matrix Frame_Matrix;
//Handlers
//-------------------------------------------------------------------------------------------------------------------------//

void handle_resize(int sig){
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0){
        perror("Error : ioctl syscall error"); 
        exit(EXIT_FAILURE);
    }

    Resize_Frame_Matrix();
    cleanup_Linux_Terminal();
    //printf("\nResize detected! New Size: %d x %d\n", w.ws_col, w.ws_row);
}

void handle_CrtlC(int sig){
    cleanup_Linux_Terminal();
    printf("\nUnexpected Termination - Exiting Safesly\n");
}

//Signals configurators 
//-------------------------------------------------------------------------------------------------------------------------//

void Configure_all_signals(){
    resize_signal_configuration();
    CrtlC_signal_configuration();
}

void resize_signal_configuration(){
    if(signal(SIGWINCH, handle_resize) == SIG_ERR){ 
        perror("Error: resize siganl configuration"); 
        exit(EXIT_FAILURE);
    }
    return 0;
}

void CrtlC_signal_configuration(){
    if(signal(SIGINT, handle_CrtlC) == SIG_ERR){ 
        perror("Error: Crtl-C siganl configuration"); 
        exit(EXIT_FAILURE);
    }
    return 0;
}