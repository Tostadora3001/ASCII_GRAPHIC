#define _POSIX_C_SOURCE 199309L
#define STANDARD_FRAME_TIME 33  //30 FPS

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>

#include "Signals_Linux.h"
#include "Data_Structs/Data_Structs.h"

//Pre declaration of external used dunctions and usefull variables
void cleanup_Linux_Terminal();
void Resize_Frame_Matrix();
void render_frame();

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

void handle_Frame_Time(struct sigevent *sev) {
    sev->sigev_notify = SIGEV_THREAD;            // Notificar mediante un hilo
    sev->sigev_notify_function = render_frame;      // Llamar a la función 
    sev->sigev_notify_attributes = NULL;         // Atributos por defecto
    sev->sigev_value.sival_int = 0;              // Argumento opcional
}

//Signals configurators 
//-------------------------------------------------------------------------------------------------------------------------//

void Configure_all_signals(){
    resize_signal_configuration();
    CrtlC_signal_configuration();
    Frame_Time_signal_configuration_Linux(STANDARD_FRAME_TIME);
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

void Frame_Time_signal_configuration_Linux(int ms) {
    delta_t = ms / 1000.0f;
    struct itimerspec its;
    struct sigevent sev;

    handle_Frame_Time(&sev);  

    if (timer_create(CLOCK_MONOTONIC, &sev, &timerid) == -1) {
        perror("Error al crear el temporizador");
        exit(EXIT_FAILURE);
    }

    its.it_value.tv_sec = ms / 1000;                        
    its.it_value.tv_nsec = (ms % 1000) * 1000000;           
    
    its.it_interval.tv_sec = its.it_value.tv_sec;           
    its.it_interval.tv_nsec = its.it_value.tv_nsec;        

    // Armar el temporizador
    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        perror("Error al armar el temporizador");
        exit(EXIT_FAILURE);
    }
}