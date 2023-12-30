typedef struct
{
    SDL_Rect *mainRect;
    SDL_Rect *processesRects[iQueueLength];

    int processesNum;
    ProcessW *processesW[iQueueLength];

} WidgetIQueue;

// init
WidgetIQueue *initWIQueue(Queue *queue)
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

            processW = initProcessW(current, processRect->w, processRect->h, processRect->x, processRect->y);
            iQueue->processesW[i] = processW;
        }
    }

    return iQueue;
};

// draw
void drawWIQueue(SDL_Renderer *renderer, WidgetIQueue *widget)
{
    
    // draw main
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);
    SDL_RenderDrawRect(renderer, widget->mainRect);

    // draw processesRects
    for (int i = 0; i < widget->processesNum; i++)
    {
        drawProcessW(renderer, widget->processesW[i]);
    }

    // draw processesRects
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);
    for (int i = 0; i < iQueueLength; i++)
    {
        SDL_RenderDrawRect(renderer, widget->processesRects[i]);
    }
}

// update
void updateWIQueue(SDL_Renderer *renderer, WidgetIQueue *widget, Queue *queue)
{

    printf("updated\n");
}
