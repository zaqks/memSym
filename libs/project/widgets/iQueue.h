typedef struct
{
    SDL_Rect *mainRect;
    SDL_Rect *processes[iQueueLength];
} WidgetIQueue;

// init
WidgetIQueue *initWIQueue(Queue *queue)
{
    WidgetIQueue *iQueue = (WidgetIQueue *)malloc(sizeof(WidgetIQueue));

    // draw the main rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->h = SCREEN_HEIGHT - MAINPADDING * 2;
    mainRect->w = MAINPADDING * 2;
    mainRect->x = MAINPADDING;
    mainRect->y = MAINPADDING;
    iQueue->mainRect = mainRect;

    // draw the processes
    SDL_Rect *processRect;
    int pWidth = mainRect->w;
    int pHeight = mainRect->h / iQueueLength;

    for (int i = 0; i < 4; i++)
    {
        processRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

        processRect->x = MAINPADDING;
        processRect->y = MAINPADDING + i*pHeight;
        processRect->w = pWidth;
        processRect->h = pHeight;

        iQueue->processes[i] = processRect;
    }

    return iQueue;
};

// draw
void drawWIQueue(SDL_Renderer *renderer, WidgetIQueue *widget)
{
    // draw main
    SDL_SetRenderDrawColor(renderer, BLUECLR.r, BLUECLR.g, BLUECLR.b, BLUECLR.a);
    SDL_RenderFillRect(renderer, widget->mainRect);

    // draw processes
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);

    for (int i = 0; i < 4; i++)
    {
        SDL_RenderDrawRect(renderer, widget->processes[i]);
    }
}

// update
void updateWIQueue(SDL_Renderer *renderer, WidgetIQueue *widget, Queue *queue)
{

    printf("updated\n");
}
