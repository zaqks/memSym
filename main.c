#include "libs/project/imports.h"

int main(int argc, char *args[])
{
    srand(time(NULL)); // set the seed

    window = initWin("memSym");
    pixelFormat = SDL_GetWindowSurface(window->win)->format;
    renderer = window->renderer;
    MAINPADDING *= window->padding;

    // structs inits
    iStack = initStack();
    for (int i = 0; i < iStackLength; i++)
    {
        pushStackNode(iStack, initQueue());
    }

    ramPartitions = initRam();

    // getUserData
    if (getUserData())
    {
        printf("userdata loaded\n");
        if (checkUserData())
        {
            // setup the structs according to the userdata
            setUserData(iStack, ramPartitions);
            printf("userdata set\n");
        }
        else
        {
            printf("userdata corrupted\n");
        }
    }

    // widgets inits
    legendW = initLengendW(renderer);
    statusW = initStatusW(renderer);

    iStackW = initWIStack();
    ramW = initRamW();

    // init sound
    initSounds();

    mainLoop(window, eventFunc, loopFunc);

    return EXIT_SUCCESS;
}