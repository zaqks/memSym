typedef struct
{
    SDL_Color color;
    SDL_Rect *mainRect;
    Text *idTxt;
} ProcessW;

TTF_Font *processFont;

ProcessW *initProcessW(SDL_Renderer *renderer, Process *process, int width, int height, int x, int y)
{
    ProcessW *widget = (ProcessW *)malloc(sizeof(ProcessW));
    // font
    if (processFont == NULL)
    {
        processFont = TTF_OpenFont("assets/fonts/QuickSand.ttf", 10);
    }

    // color
    widget->color.r = randomNum(0, 255);
    widget->color.g = randomNum(0, 255);
    widget->color.b = randomNum(0, 255);
    widget->color.a = 255;

    // main Rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->x = x;
    mainRect->y = y;
    mainRect->w = width;
    mainRect->h = height;

    widget->mainRect = mainRect;

    // text
    
    char* idVal = (char*) malloc(10);
    sprintf(idVal, "%d", process->id);
    Text *idText = createText(renderer, processFont, NULL, 0, idVal, widget->color, x, y);
    widget->idTxt = idText;
    

    return widget;
}

void drawProcessW(SDL_Renderer *renderer, ProcessW *process)
{
    //draw body
    SDL_SetRenderDrawColor(renderer, process->color.r,
                           process->color.g,
                           process->color.b,
                           process->color.a);
    SDL_RenderDrawRect(renderer, process->mainRect);

    //draw text
    drawText(renderer, process->idTxt);

}
