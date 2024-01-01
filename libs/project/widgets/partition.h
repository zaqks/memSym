typedef struct
{
    SDL_Rect *mainRect;
    Text *addrTxt;
    List *processW;

} WidgetPartition;

TTF_Font *addrFont;

WidgetPartition *initPartitionW(SDL_Renderer *renderer, Partition *partition, int w, int h, int x, int y)
{
    if (addrFont == NULL)
    {
        addrFont = TTF_OpenFont("assets/fonts/QuickSand.ttf", 10);
    }

    WidgetPartition *widget = (WidgetPartition *)malloc(sizeof(WidgetPartition));

    // main rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->x = x;
    mainRect->y = y;
    mainRect->w = w;
    mainRect->h = h;

    widget->mainRect = mainRect;

    // addr txt
    char *addrVal = (char *)malloc(20);
    sprintf(addrVal, "%p", partition->startAdr);
    Text *addrTxt = createText(renderer, addrFont, NULL, 0, addrVal, WHITECLR, mainRect->x, mainRect->y);
    addrTxt->rect->x += (w - addrTxt->rect->w) / 2;
    addrTxt->rect->y += (w - addrTxt->rect->w) / 2;

    widget->addrTxt = addrTxt;

    return widget;
}

void drawPartitionW(SDL_Renderer *renderer, WidgetPartition *widget)
{
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);
    // main rect
    SDL_RenderDrawRect(renderer, widget->mainRect);
    // addr txt
    drawText(renderer, widget->addrTxt);
}

void erasePartitionW(WidgetPartition *widget)
{
    // processes

    // main rect
    free(widget->mainRect);
    // txt
    eraseText(widget->addrTxt);

    // widget
    free(widget);
}


