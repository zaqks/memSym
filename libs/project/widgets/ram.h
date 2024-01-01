

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
    ListNode *current = widget->partitionsW->head;
    for (int i = 0; i < widget->partitionsW->length; i++)
    {
        drawPartitionW(renderer, current->val);
        current = current->next;
    }

    // printf("draw ram\n");
}

void updateRawW(SDL_Renderer *renderer, WidgetRam *widget, Ram *ram)
{
    // delete partitionsW
    ListNode *currentW = widget->partitionsW->head;

    while (widget->partitionsW->length)
    {
        erasePartitionW(currentW->val);
        currentW = currentW->next;
        removeListNode(widget->partitionsW, 0);
    }

    // get the max size
    int maxSize = 0;
    ListNode *current = ram->partitions->head;

    for (int i = 0; i < ram->partitions->length; i++)
    {
        if (maxSize < ((Partition *)(current->val))->size)
        {
            maxSize = ((Partition *)(current->val))->size;
        }

        current = current->next;
    }

    // create the partitions
    int pW = (widget->grpRect->w - (ram->partitions->length + 1) * MAINPADDING) / ram->partitions->length;
    if (pW > SCREEN_WIDTH / 10)
    {
        pW = SCREEN_WIDTH / 10;
    }
    int pH = widget->grpRect->h - MAINPADDING * 2;

    int x = widget->grpRect->x + (widget->grpRect->w - (pW + MAINPADDING) * ram->partitions->length + MAINPADDING) / 2;
    int y = widget->grpRect->y + MAINPADDING;

    current = ram->partitions->head;
    WidgetPartition *partitionW;

    for (int i = 0; i < ram->partitions->length; i++)
    {
        partitionW = initPartitionW(renderer, current->val, pW, pH * ((float)((Partition *)(current->val))->size / maxSize), x + i * pW + (i)*MAINPADDING, y);
        addListNode1(widget->partitionsW, partitionW);
        current = current->next;
    }

    // printf("update ram\n");
}
