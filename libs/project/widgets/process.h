typedef struct
{
    SDL_Rect *mainRect;
    Text *text;
} ProcessW;

ProcessW *initProcessW(Process *process, int width, int height, int x, int y)
{
    ProcessW *widget = (ProcessW *)malloc(sizeof(ProcessW));

    // main Rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->x = x;
    mainRect->y = y;
    mainRect->w = width;
    mainRect->h = height;

    return widget;
}

void drawProcessW(SDL_Renderer *renderer, ProcessW *process) {}
