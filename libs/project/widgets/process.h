typedef struct
{
    SDL_Color color;
    SDL_Rect *mainRect;
    Text *idTxt;
    Text *szTxt;
} WidgetProcess;

#define txtPadding 5
TTF_Font *processFont;

WidgetProcess *initProcessW(SDL_Renderer *renderer, Process *process, int width, int height, int x, int y)
{
    WidgetProcess *widget = (WidgetProcess *)malloc(sizeof(WidgetProcess));
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

    char *idVal = (char *)malloc(10);
    sprintf(idVal, "%d", process->id);
    Text *idText = createText(renderer, processFont, NULL, 0, idVal, widget->color, x + txtPadding, y + txtPadding);
    widget->idTxt = idText;

    char *sizeVal = (char *)malloc(10);
    sprintf(sizeVal, "%dB", process->size);
    Text *sizeText = createText(renderer, processFont, NULL, 0, sizeVal, widget->color, x, y);
    sizeText->rect->x += mainRect->w - sizeText->rect->w - txtPadding;
    sizeText->rect->y += mainRect->h - sizeText->rect->h - txtPadding;

    widget->szTxt = sizeText;

    return widget;
}

void drawProcessW(SDL_Renderer *renderer, WidgetProcess *process)
{
    // draw body
    SDL_SetRenderDrawColor(renderer, process->color.r,
                           process->color.g,
                           process->color.b,
                           process->color.a);
    SDL_RenderDrawRect(renderer, process->mainRect);

    // draw text
    drawText(renderer, process->idTxt);
    drawText(renderer, process->szTxt);
}

void eraseProcessW(WidgetProcess *process)
{
    eraseText(process->idTxt);
    eraseText(process->szTxt);
    free(process);
}