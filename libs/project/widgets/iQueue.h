typedef struct
{
    SDL_Rect *mainRect;
    SDL_Rect *processesRects[iQueueLength];

    int processesNum;
    WidgetProcess *processesW[iQueueLength];

} WidgetIQueue;

// init
WidgetIQueue *initWIQueue()
{
    WidgetIQueue *iQueue = (WidgetIQueue *)malloc(sizeof(WidgetIQueue));
    iQueue->processesNum = 0;

    // create the body rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->h = SCREEN_HEIGHT - MAINPADDING * 2;
    mainRect->w = SCREEN_WIDTH / 10;
    mainRect->x = MAINPADDING;
    mainRect->y = MAINPADDING;
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

        processRect->x = MAINPADDING;
        processRect->y = (mainRect->h - pHeight + 2 * MAINPADDING) - (MAINPADDING + i * pHeight);
        processRect->w = pWidth;
        processRect->h = pHeight;

        iQueue->processesRects[i] = processRect;

        // create the processes
        /*
                if (i < iQueue->processesNum)
                {
                    current = (Process *)popQueueNode(queue);
                    pushQueueNode(queue, current);

                    processW = initProcessW(renderer, current, processRect->w, processRect->h, processRect->x, processRect->y);
                    iQueue->processesW[i] = processW;
                }
        */
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
