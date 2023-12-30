#include "libs/project/imports.h"
#include "libs/dataStructs/process.h"

int main(int argc, char *args[])
{

    window = initWin("memSym");
    pixelFormat = SDL_GetWindowSurface(window->win)->format;
    renderer = window->renderer;

    legendW = initLengendW(renderer);

    iQueue = initQueue();
    iQueueW = initWIQueue(iQueue);

    eventLoop(window, eventFunc, loopFunc);

    return 0;
}