#define StatusNum 8
char *statusVals[StatusNum] = {
    "processor ",
    "queue ",
    "first fit ",
    "best fit ",
    "worst fit ",
    "priority",
    "print iStack",
    "sound",
};

const int statusPadding = 10;
TTF_Font *statusFont;

typedef struct
{
    SDL_Rect *mainRect;
    Text *txt[StatusNum];
    Text *vals[StatusNum];

} WidgetStatus;

WidgetStatus *initStatusW(SDL_Renderer *renderer)
{
    statusFont = TTF_OpenFont("assets/fonts/QuickSand.ttf", 15);
    WidgetStatus *status = (WidgetStatus *)malloc(sizeof(WidgetStatus));

    // create text
    int previousY = 0;
    int mainRectH = 0;

    Text *txt;
    for (int i = 0; i < StatusNum; i++)
    {
        txt = createText(renderer, statusFont, NULL, 0, statusVals[i], WHITECLR, 0, 0);

        status->txt[i] = txt;
        txt->rect->y = previousY;
        previousY += txt->rect->h;
        // calc rect dims
        mainRectH += txt->rect->h;
        // get max width
    }

    // create vals
    previousY = 0;
    Text *valTxt;
    for (int i = 0; i < StatusNum; i++)
    {

        valTxt = createText(renderer, statusFont, NULL, 0, "<off>", REDCLR, 0, 0);

        status->vals[i] = valTxt;
        valTxt->rect->y = previousY;
        previousY += valTxt->rect->h;
    }

    // create rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->h = mainRectH + 2 * statusPadding;
    mainRect->w = legendW->mainRect->w;
    mainRect->x = legendW->mainRect->x;
    mainRect->y = MAINPADDING;

    status->mainRect = mainRect;

    // text postion
    for (int i = 0; i < StatusNum; i++)
    {
        txt = status->txt[i];
        valTxt = status->vals[i];

        valTxt->rect->x += mainRect->x + statusPadding;
        valTxt->rect->y += mainRect->y + statusPadding;

        txt->rect->x += valTxt->rect->x + valTxt->rect->w + statusPadding;
        txt->rect->y += mainRect->y + statusPadding;
    }

    return status;
}

void updateStatusW(SDL_Renderer *renderer, WidgetStatus *widget, bool processor, bool queue, int strategy, int priority, bool sound, int printIndx)
{
    // processor + queue
    int vals[2] = {processor, queue};

    for (int i = 0; i < 2; i++)
    {
        if (vals[i])
        {
            changeTextColor(widget->vals[i], GREENCLR);
            updateText(renderer, widget->vals[i], "<on>");
        }
        else
        {
            changeTextColor(widget->vals[i], REDCLR);
            updateText(renderer, widget->vals[i], "<off>");
        }
    }

    // strategy
    for (int i = 2; i < 5; i++)
    {
        if (i - 2 == strategy)
        {
            changeTextColor(widget->vals[i], GREENCLR);
            updateText(renderer, widget->vals[i], "<on>");
        }
        else
        {
            changeTextColor(widget->vals[i], REDCLR);
            updateText(renderer, widget->vals[i], "<off>");
        }
    }

    // priority
    if (priority)
    {
        changeTextColor(widget->vals[StatusNum - 3], GREENCLR);
        updateText(renderer, widget->vals[StatusNum - 3], "<on>");
    }
    else
    {
        changeTextColor(widget->vals[StatusNum - 3], REDCLR);
        updateText(renderer, widget->vals[StatusNum - 3], "<off>");
    }

    // print mode
    if (printIndx )
    {
        changeTextColor(widget->vals[StatusNum - 2], GREENCLR);
        updateText(renderer, widget->vals[StatusNum - 2], "<on>");
    }
    else
    {
        changeTextColor(widget->vals[StatusNum - 2], REDCLR);
        updateText(renderer, widget->vals[StatusNum - 2], "<off>");
    }

    // sound
    if (sound)
    {
        changeTextColor(widget->vals[StatusNum - 1], GREENCLR);
        updateText(renderer, widget->vals[StatusNum - 1], "<on>");
    }
    else
    {
        changeTextColor(widget->vals[StatusNum - 1], REDCLR);
        updateText(renderer, widget->vals[StatusNum - 1], "<off>");
    }
}

void drawStatusW(SDL_Renderer *renderer, WidgetStatus *widget)
{
    // draw rect
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);
    SDL_RenderDrawRect(renderer, widget->mainRect);

    // draw text

    for (int i = 0; i < StatusNum; i++)
    {
        drawText(renderer, widget->txt[i]);
        drawText(renderer, widget->vals[i]);
    }
}
