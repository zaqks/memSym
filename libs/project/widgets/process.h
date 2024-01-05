typedef struct
{
    SDL_Color color;
    SDL_Rect *mainRect;
    Text *szTxt;
    Text *clkTxt;
    Text *priorityTxt;

    int id;
    Text *idTxt;

} WidgetProcess;

#define txtPadding 5
TTF_Font *processFont;

WidgetProcess *initProcessW(SDL_Renderer *renderer, Process *process, int width, int height, int x, int y)
{
    WidgetProcess *widget = (WidgetProcess *)malloc(sizeof(WidgetProcess));
    widget->id = process->id;
    // font
    if (processFont == NULL)
    {
        processFont = TTF_OpenFont("assets/fonts/QuickSand.ttf", 10);
    }

    // color
    widget->color.r = process->color.r;
    widget->color.g = process->color.g;
    widget->color.b = process->color.b;
    widget->color.a = process->color.a;

    // main Rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->x = x;
    mainRect->y = y;
    mainRect->w = width;
    mainRect->h = height;

    widget->mainRect = mainRect;

    // id text

    char *idVal = (char *)malloc(10);
    sprintf(idVal, "%d", process->id);
    Text *idText = createText(renderer, processFont, NULL, 0, idVal, widget->color, x + txtPadding, y + txtPadding);
    widget->idTxt = idText;

    // size text

    char *sizeVal = (char *)malloc(10);
    sprintf(sizeVal, "%dB", process->size);
    Text *sizeText = createText(renderer, processFont, NULL, 0, sizeVal, widget->color, x, y);
    sizeText->rect->x += mainRect->w - sizeText->rect->w - txtPadding;
    sizeText->rect->y += mainRect->h - sizeText->rect->h - txtPadding;
    widget->szTxt = sizeText;

    // clock text
    char *clkVal = (char *)malloc(10);
    sprintf(clkVal, "%dC", process->clocks);
    Text *clkText = createText(renderer, processFont, NULL, 0, clkVal, widget->color, x, y);
    clkText->rect->x += txtPadding;
    clkText->rect->y += mainRect->h - sizeText->rect->h - txtPadding;
    widget->clkTxt = clkText;

    // priotrity text
    char *prVal = (char *)malloc(2);
    sprintf(prVal, "%d", process->priority);

    Text *prText = createText(renderer, processFont, NULL, 0, prVal, widget->color, x, idText->rect->y);
    prText->rect->x += mainRect->w - prText->rect->w - txtPadding;
    widget->priorityTxt = prText;

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
    drawText(renderer, process->clkTxt);
    drawText(renderer, process->priorityTxt);
}

void eraseProcessW(WidgetProcess *process)
{
    free(process->mainRect);
    eraseText(process->idTxt);
    eraseText(process->szTxt);
    eraseText(process->clkTxt);
    eraseText(process->priorityTxt);
    free(process);
}