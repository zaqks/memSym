typedef struct
{
    SDL_Rect *mainRect;
    SDL_Rect *processesRects[iQueueLength];

    int processesNum;
    ProcessW *processesW[iQueueLength];

} WidgetIQueue;

// init
WidgetIQueue *initWIQueue(SDL_Renderer *renderer, Queue *queue)
{
    WidgetIQueue *iQueue = (WidgetIQueue *)malloc(sizeof(WidgetIQueue));
    iQueue->processesNum = queue->length;

    // create the body rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->h = SCREEN_HEIGHT - MAINPADDING * 2;
    mainRect->w = MAINPADDING * 2;
    mainRect->x = MAINPADDING;
    mainRect->y = MAINPADDING;
    iQueue->mainRect = mainRect;

    // create the processesRects
    SDL_Rect *processRect;
    int pWidth = mainRect->w;
    int pHeight = mainRect->h / iQueueLength;

    ProcessW *processW;
    Process *current;
    for (int i = 0; i < iQueueLength; i++)
    {
        processRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

        processRect->x = MAINPADDING;
        processRect->y = MAINPADDING + i * pHeight;
        processRect->w = pWidth;
        processRect->h = pHeight;

        iQueue->processesRects[i] = processRect;

        // create the processes

        if (i < iQueue->processesNum)
        {
            current = (Process *)popQueueNode(queue);

            processW = initProcessW(renderer, current, processRect->w, processRect->h, processRect->x, processRect->y);
            iQueue->processesW[i] = processW;
        }
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

    printf("updated\n");
}
