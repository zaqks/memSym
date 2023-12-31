typedef struct
{
    SDL_Rect *mainRect;

} WidgetRam;

WidgetRam *initRamW()
{
    WidgetRam *widget = (WidgetRam *)malloc(sizeof(WidgetRam));

    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->x = MAINPADDING * 2 + SCREEN_WIDTH / 10;
    mainRect->y = MAINPADDING;
    mainRect->w = SCREEN_WIDTH - SCREEN_WIDTH / 10 - 3*MAINPADDING;
    mainRect->h = SCREEN_HEIGHT - MAINPADDING * 2;

    widget->mainRect = mainRect;

    return widget;
}

void drawRawW(SDL_Renderer *renderer, WidgetRam *widget)
{
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);
    //
    SDL_RenderDrawRect(renderer, widget->mainRect);
}

void updateRawW(SDL_Renderer *renderer, WidgetRam *widget) {}
