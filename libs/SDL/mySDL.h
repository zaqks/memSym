#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define REFRESHRATE 33

typedef struct
{
    int width;
    int height;
    SDL_Window *win;
    // SDL_Surface *surface;
    SDL_Renderer *renderer;
} Window;

Window *initWin(char *title)
{
    Window *newWin = (Window *)malloc(sizeof(Window));
    newWin->width = SCREEN_WIDTH;
    newWin->height = SCREEN_HEIGHT;

    char *newTitle = "window";
    if (title != NULL)
    {
        newTitle = title;
    }
    SDL_Init(SDL_INIT_EVERYTHING);
    newWin->win = SDL_CreateWindow(newTitle, 50, 50, newWin->width, newWin->height, SDL_WINDOW_SHOWN);

    TTF_Init();
    /*
    newWin->surface = SDL_GetWindowSurface(newWin->win);
    SDL_FillRect(newWin->surface, NULL, SDL_MapRGB(newWin->surface->format, 0xFF, 0x00, 0x00));

    SDL_UpdateWindowSurface(newWin->win);
    */
    newWin->renderer = SDL_CreateRenderer(newWin->win, -1, 0);
    SDL_SetRenderDrawColor(newWin->renderer, 0, 0, 0, 255);
    SDL_RenderClear(newWin->renderer);
    return newWin;
}

void killWin(Window *win)
{
    // kill widnow
    SDL_DestroyWindow(win->win);

    // quit sdl
    SDL_Quit();

    free(win);
}

void eventLoop(Window *win, void (*eFunc)(SDL_Event e), void (*func)(Window *win))
{
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
            //
            if (eFunc != NULL)
            {
                (*eFunc)(e);
            }
            //
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        if (func != NULL)
        {
            (*func)(win);
        }

        SDL_Delay(REFRESHRATE);
    }
    killWin(win);
}
