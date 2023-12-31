

typedef struct
{
    SDL_Rect *mainRect;
    SDL_Rect *grpRect;
    //
    List *partitionsW;

} WidgetRam;

WidgetRam *initRamW()
{
    WidgetRam *widget = (WidgetRam *)malloc(sizeof(WidgetRam));

    // main rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->x = MAINPADDING * 2 + SCREEN_WIDTH / 10;
    mainRect->y = MAINPADDING;
    mainRect->w = SCREEN_WIDTH - SCREEN_WIDTH / 10 - 3 * MAINPADDING;
    mainRect->h = SCREEN_HEIGHT - MAINPADDING * 2;
    widget->mainRect = mainRect;

    // group rect
    SDL_Rect *grpRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    widget->grpRect = grpRect;
    grpRect->x = mainRect->x;
    grpRect->y = mainRect->y;
    grpRect->w = mainRect->w - legendW->mainRect->w;
    grpRect->h = mainRect->h;

    // partitionLst
    widget->partitionsW = initList();

    return widget;
}

void drawRawW(SDL_Renderer *renderer, WidgetRam *widget)
{
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);

    // main Rect
    SDL_RenderDrawRect(renderer, widget->mainRect);
    // group Rect
    SDL_RenderDrawRect(renderer, widget->grpRect);

    // partitions
}

void updateRawW(SDL_Renderer *renderer, WidgetRam *widget, Ram *ram)
{
    // delete partitionsW
    int partitionsNum = widget->partitionsW->length;
    for (int i = 0; i < partitionsNum; i++)
    {
        erasePartitionW()
    }

    // create the partitions
}
