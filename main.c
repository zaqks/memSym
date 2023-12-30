#include "libs/project/imports.h"

int main(int argc, char *args[])
{
    srand(time(NULL)); // set the seed

    window = initWin("memSym");
    pixelFormat = SDL_GetWindowSurface(window->win)->format;
    renderer = window->renderer;

    legendW = initLengendW(renderer);

    iQueue = initQueue();

    // add processes
    Process *process;
    for (int i = 0; i < 10; i++)
    {
        process = initProcess();
        pushProcessQueue(iQueue, process);
    }

    iQueueW = initWIQueue(iQueue);

    eventLoop(window, eventFunc, loopFunc);

    return 0;
}