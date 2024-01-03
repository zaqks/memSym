#include "libs/project/imports.h"

int main(int argc, char *args[])
{
    srand(time(NULL)); // set the seed

    window = initWin("memSym");
    pixelFormat = SDL_GetWindowSurface(window->win)->format;
    renderer = window->renderer;
    MAINPADDING *= window->padding;

    //structs inits
    iQueue = initQueue();
    ramPartitions = initRam();
    
    //widgets inits
    legendW = initLengendW(renderer);
    statusW = initStatusW(renderer);
    iQueueW = initWIQueue();
    ramW = initRamW();
    
    eventLoop(window, eventFunc, loopFunc);

    return 0;
}