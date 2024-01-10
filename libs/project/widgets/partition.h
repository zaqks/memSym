const int partnPdng = 8;

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
    sprintf(addrVal, "%p", partition->startAdr->arr);
    Text *addrTxt = createText(renderer, addrFont, NULL, 0, addrVal, WHITECLR, mainRect->x, mainRect->y);
    // addrTxt->rect->x += (w - addrTxt->rect->w) / 2;
    // addrTxt->rect->y += (w - addrTxt->rect->w) / 2;
    addrTxt->rect->x += partnPdng;
    addrTxt->rect->y += mainRect->h - addrTxt->rect->h - partnPdng;

    widget->addrTxt = addrTxt;

    // processes
    widget->processW = initList();

    Array *processes = partition->startAdr;
    Process *current;
    WidgetProcess *processW;

    int pH = 0;
    if (processes->length)
    {
        pH = (mainRect->h - addrTxt->rect->h - partnPdng * 2) / processes->length;
    }

    for (int i = 0; i < processes->length; i++)
    {
        current = (Process *)(processes->arr[i].val);
        processW = initProcessW(renderer, current, mainRect->w, pH, mainRect->x, mainRect->y + i * pH);
        addListNode1(widget->processW, processW);
    }

    return widget;
}

void drawPartitionW(SDL_Renderer *renderer, WidgetPartition *widget)
{
    SDL_Color partitonCLR;
    if (getListLength(widget->processW))
    {
        partitonCLR = REDCLR;
    }
    else
    {
        partitonCLR = GREENCLR;
    }

    SDL_SetRenderDrawColor(renderer, partitonCLR.r, partitonCLR.g, partitonCLR.b, partitonCLR.a);
    // main rect
    SDL_RenderDrawRect(renderer, widget->mainRect);

    // processes
    Stack *toDraw = initStack();

    ListNode *current = widget->processW->head;
    while (current)
    {
        pushStackNode(toDraw, current->val);
        current = current->next;
    }
    while (!emptyStack(toDraw))
    {
        drawProcessW(renderer, popStackNode(toDraw));
    }

    free(toDraw);

    // addr txt
    drawText(renderer, widget->addrTxt);
}

void erasePartitionW(WidgetPartition *widget)
{
    // processes
    ListNode *current = widget->processW->head;
    while (current != NULL)
    {
        eraseProcessW(current->val);
        current = current->next;
    }

    // main rect
    free(widget->mainRect);
    // txt
    eraseText(widget->addrTxt);
    // widget
    free(widget);
}
