typedef struct
{
    SDL_Color color;
    SDL_Rect *mainRect;
    Parallelogram *face1;
    Parallelogram *face2;

    Text *szTxt;
    Text *clkTxt;
    Text *priorityTxt;

    int id;
    Text *idTxt;

    Array *levels;

} WidgetProcess;

#define txtPadding 5
#define beta 45
#define maxProcZ 50

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

    // 3d faces

    // face2
    // double b = atan((double)width / height);

    double zH = maxProcZ;
    if (process->clocks > 1)
    {
        zH *= ((double)process->clocks / MaxProcCLK);
    }

    Parallelogram *face2 = initParallelogram(x, y, zH * sin(beta), height, 0, -zH * cos(beta));
    widget->face2 = face2;

    mainRect->x += face2->w;
    mainRect->y += face2->y3;
    // face1
    Parallelogram *face1 = initParallelogram(x + face2->w, y + face2->h + face2->y3, width, zH * cos(beta), -face2->w, 0);
    widget->face1 = face1;

    // levels
    widget->levels = initArray();
    if (process->clocks > 0)
    {
        Parallelogram *currentLevel;
        for (int i = 1; i < process->clocks + 1; i++)
        {
            // face2
            currentLevel = initParallelogram(
                face2->x1,
                face2->y1,
                face2->w * i / process->clocks,
                face2->h,
                face2->x3,
                face2->y3 * i / process->clocks);

            pushArrayNode(widget->levels, currentLevel);

            // face1
            currentLevel = initParallelogram(
                face1->x1,
                face1->y1,
                face1->w,
                face1->h * i / process->clocks,
                face1->x3 * i / process->clocks,
                face1->y3);

            pushArrayNode(widget->levels, currentLevel);
        }
    }

    // id text

    char *idVal = (char *)malloc(10);
    sprintf(idVal, "%d", process->id);
    Text *idText = createText(renderer, processFont, NULL, 0, idVal, widget->color, mainRect->x + txtPadding, mainRect->y + txtPadding);
    widget->idTxt = idText;

    // size text

    char *sizeVal = (char *)malloc(10);
    sprintf(sizeVal, "%dB", process->size);
    Text *sizeText = createText(renderer, processFont, NULL, 0, sizeVal, widget->color, mainRect->x, mainRect->y);
    sizeText->rect->x += mainRect->w - sizeText->rect->w - txtPadding;
    sizeText->rect->y += mainRect->h - sizeText->rect->h - txtPadding;
    widget->szTxt = sizeText;

    // clock text
    char *clkVal = (char *)malloc(10);
    sprintf(clkVal, "%dC", process->clocks);
    Text *clkText = createText(renderer, processFont, NULL, 0, clkVal, widget->color, mainRect->x, mainRect->y);
    clkText->rect->x += txtPadding;
    clkText->rect->y += mainRect->h - sizeText->rect->h - txtPadding;
    widget->clkTxt = clkText;

    // priotrity text
    char *prVal = (char *)malloc(2);
    sprintf(prVal, "%d", process->priority);

    Text *prText = createText(renderer, processFont, NULL, 0, prVal, widget->color, mainRect->x, idText->rect->y);
    prText->rect->x += mainRect->w - prText->rect->w - txtPadding;
    widget->priorityTxt = prText;

    return widget;
}

void drawProcessW(SDL_Renderer *renderer, WidgetProcess *process)
{

    // draw 3d faces
    SDL_SetRenderDrawColor(renderer, process->color.r,
                           process->color.g,
                           process->color.b,
                           process->color.a);
    drawParallelogram(renderer, process->face1, true);

    SDL_SetRenderDrawColor(renderer, process->color.r,
                           process->color.g,
                           process->color.b,
                           process->color.a);
    drawParallelogram(renderer, process->face2, true);

    // draw facing area
    SDL_SetRenderDrawColor(renderer, BGCLR.r,
                           BGCLR.g,
                           BGCLR.b,
                           BGCLR.a);
    SDL_RenderFillRect(renderer, process->mainRect);
    SDL_RenderDrawRect(renderer, process->mainRect);

    // draw levels

    for (int i = 0; i < process->levels->length; i++)
    {
        drawParallelogram(renderer, process->levels->arr[i].val, 0);
    }

    // draw outlines
    SDL_SetRenderDrawColor(renderer, WHITECLR.r,
                           WHITECLR.g,
                           WHITECLR.b,
                           WHITECLR.a);

    drawParallelogram(renderer, process->face2, 0);
    drawParallelogram(renderer, process->face1, 0);
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
    free(process->face1);
    free(process->face2);

    freeArray(process->levels);

    eraseText(process->idTxt);
    eraseText(process->szTxt);
    eraseText(process->clkTxt);
    eraseText(process->priorityTxt);
    free(process);
}