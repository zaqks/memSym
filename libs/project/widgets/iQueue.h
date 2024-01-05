typedef struct
{
    SDL_Rect *mainRect;
    SDL_Rect *processesRects[iQueueLength];

    int processesNum;
    WidgetProcess *processesW[iQueueLength];

} WidgetIQueue;

// init
WidgetIQueue *initWIQueue(int w, int h, int x, int y)
{
    WidgetIQueue *iQueue = (WidgetIQueue *)malloc(sizeof(WidgetIQueue));
    iQueue->processesNum = 0;

    // create the body rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->x = x;
    mainRect->y = y;
    mainRect->w = w;
    mainRect->h = h;

    iQueue->mainRect = mainRect;

    // create the processesRects
    SDL_Rect *processRect;
    int pWidth = mainRect->w;
    int pHeight = mainRect->h / iQueueLength;

    WidgetProcess *processW;
    Process *current;
    for (int i = 0; i < iQueueLength; i++)
    {
        processRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

        processRect->x = mainRect->x;
        processRect->y = mainRect->y + mainRect->h - pHeight - i * pHeight;
        processRect->w = pWidth;
        processRect->h = pHeight;

        iQueue->processesRects[i] = processRect;
    }

    return iQueue;
};

// draw
void drawWIQueue(SDL_Renderer *renderer, WidgetIQueue *widget)
{
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);

    // draw main
    SDL_RenderDrawRect(renderer, widget->mainRect);

    // draw processesRects
    for (int i = 0; i < iQueueLength; i++)
    {
        SDL_RenderDrawRect(renderer, widget->processesRects[i]);
    }

    // draw processesRects
    for (int i = 0; i < widget->processesNum; i++)
    {
        drawProcessW(renderer, widget->processesW[i]);
    }
}

// update
void updateWIQueue(SDL_Renderer *renderer, WidgetIQueue *widget, Queue *queue)
{

    // erase
    for (int i = 0; i < widget->processesNum; i++)
    {
        eraseProcessW(widget->processesW[i]);
    }

    // redraw
    SDL_Rect *processRect; // border
    Process *current;
    for (int i = 0; i < queue->length; i++)
    {
        processRect = widget->processesRects[i]; // border
        current = (Process *)popQueueNode(queue);
        pushQueueNode(queue, current);
        widget->processesW[i] =
            initProcessW(renderer, current, processRect->w, processRect->h, processRect->x, processRect->y);
    }
    widget->processesNum = queue->length;
}
