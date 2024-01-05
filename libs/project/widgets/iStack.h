
typedef struct
{
    SDL_Rect *mainRect;
    WidgetIQueue *queuesW[iStackLength];
} WidgetIStack;

WidgetIStack *initWIStack()
{
    WidgetIStack *widget = (WidgetIStack *)malloc(sizeof(WidgetIStack));

    // mainRect
    SDL_Rect *mainRect = malloc(sizeof(SDL_Rect));
    mainRect->w = SCREEN_WIDTH / 20;
    mainRect->w *= iStackLength;
    mainRect->w += (iStackLength - 1) * MAINPADDING / 2;

    mainRect->h = SCREEN_HEIGHT - MAINPADDING * 2;
    mainRect->x = MAINPADDING;
    mainRect->y = MAINPADDING;

    widget->mainRect = mainRect;

    // iQueues

    int iQueueWidth = (mainRect->w - (iStackLength - 1) * MAINPADDING / 2) / iStackLength;
    for (int i = 0; i < iStackLength; i++)
    {
        widget->queuesW[i] = initWIQueue(iQueueWidth, mainRect->h, mainRect->x + iQueueWidth * i + MAINPADDING / 2 * i, mainRect->y);
    }

    return widget;
}

void drawWIStack(SDL_Renderer *renderer, WidgetIStack *widget)
{
    /*
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);
    // mainRect
    SDL_RenderDrawRect(renderer, widget->mainRect);
    */

    // draw iQueues
    for (int i = 0; i < iStackLength; i++)
    {
        drawWIQueue(renderer, widget->queuesW[i]);
    }
}

void updateWIStack(SDL_Renderer *renderer, WidgetIStack *widget, Stack *stack)
{
    Stack *tmpStack = initStack();
    //
    Queue *currentQueue;
    int currentNodeIndx = 0;
    while (stack->length)
    {
        currentQueue = popStackNode(stack);
        pushStackNode(tmpStack, currentQueue);

        updateWIQueue(renderer, widget->queuesW[currentNodeIndx], currentQueue);

        currentNodeIndx += 1;
    }

    // refill
    while (tmpStack->length)
    {
        pushStackNode(stack, popStackNode(tmpStack));
    }
    free(tmpStack);
}
