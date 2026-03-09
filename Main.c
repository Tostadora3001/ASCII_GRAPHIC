#include "src/Graphic.h"
#include "src/vector3D.h"
#include "src/Signals_Linux.h"

int main(){
    atexit(cleanup_Linux_Terminal);
}