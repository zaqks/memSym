typedef struct
{
    SDL_Color color;
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

    // color

    widget->color.r = randomNum(0, 255);
    widget->color.g = randomNum(0, 255);
    widget->color.b = randomNum(0, 255);
    widget->color.a = 255;

    widget->mainRect = mainRect;

    return widget;
}

void drawProcessW(SDL_Renderer *renderer, ProcessW *process)
{
    SDL_SetRenderDrawColor(renderer, process->color.r,
                           process->color.g,
                           process->color.b,
                           process->color.a);
    SDL_RenderFillRect(renderer, process->mainRect);
}
