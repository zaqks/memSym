#include "libs/project/imports.h"

int main(int argc, char *args[])
{
    srand(time(NULL)); // set the seed

    window = initWin("memSym");
    pixelFormat = SDL_GetWindowSurface(window->win)->format;
    renderer = window->renderer;
    MAINPADDING *= window->padding;

    
    iQueue = initQueue();
    ramPartitions = initRam();
    
    legendW = initLengendW(renderer);
    iQueueW = initWIQueue(renderer, iQueue);
    ramW = initRamW();
    
    eventLoop(window, eventFunc, loopFunc);

    return 0;
}