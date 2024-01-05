#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define REFRESHRATE 33

#define FULLSCREEN true


int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 780;

typedef struct
{
    int width;
    int height;
    SDL_Window *win;
    SDL_Renderer *renderer;
    //
    int padding;
} Window;

Window *initWin(char *title)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(SDL_INIT_VIDEO);

    if (FULLSCREEN)
    {
        SDL_DisplayMode dm;
        SDL_GetDesktopDisplayMode(0, &dm);
        SCREEN_WIDTH = dm.w;
        SCREEN_HEIGHT = dm.h;
    }

    Window *newWin = (Window *)malloc(sizeof(Window));

    newWin->width = SCREEN_WIDTH;
    newWin->height = SCREEN_HEIGHT;
    newWin->padding = SCREEN_WIDTH / SCREEN_HEIGHT;

    char *newTitle = "window";
    if (title != NULL)
    {
        newTitle = title;
    }

    newWin->win = SDL_CreateWindow(newTitle, 10, 10, newWin->width, newWin->height, SDL_WINDOW_SHOWN);

    if (FULLSCREEN)
    {
        SDL_SetWindowFullscreen(newWin->win, FULLSCREEN);
        SDL_ShowCursor(0);
    }

    newWin->renderer = SDL_CreateRenderer(newWin->win, -1, 0);
    SDL_SetRenderDrawColor(newWin->renderer, 0, 0, 0, 255);
    SDL_RenderClear(newWin->renderer);

    TTF_Init();

    return newWin;
}

void killWin(Window *win)
{
    // kill widnow
    SDL_DestroyWindow(win->win);

    // quit sdl
    SDL_Quit();

    free(win);
}

void mainLoop(Window *win, void (*eFunc)(SDL_Event e), void (*func)(Window *win))
{
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
            //
            if (eFunc != NULL)
            {
                (*eFunc)(e);
            }
            //
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        if (func != NULL)
        {
            (*func)(win);
        }

        SDL_Delay(REFRESHRATE);
    }
    killWin(win);
}

SDL_PixelFormat *pixelFormat;

SDL_Color BGCLR = {0, 0, 0, 255};
SDL_Color TXTCLR = {255, 255, 255, 255};

SDL_Color WHITECLR = {255, 255, 255, 255};
SDL_Color GREENCLR = {0, 255, 0, 255};
SDL_Color REDCLR = {255, 0, 0, 255};
SDL_Color BLUECLR = {0, 0, 255, 255};
//

int MAINPADDING = 20;//*ratio w:h
#include <stdlib.h>
#include <stdio.h>

typedef struct listNode
{
    void *val;
    struct listNode *next;
} ListNode;

typedef struct
{
    int length;
    ListNode *head;
    ListNode *queue;
} List;

List *initList()
{
    List *lst = (List *)malloc(sizeof(List));
    lst->head = NULL;
    lst->length = 0;
}
// queue mode
void addListNode1(List *lst, void *val)
{
    ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
    newElem->val = val;
    newElem->next = NULL;

    if (lst->length == 0)
    {
        lst->head = newElem;
    }
    else
    {
        lst->queue->next = newElem;
    }
    lst->queue = newElem;
    lst->length += 1;
}
// stack mode
void addListNode2(List *lst, void *val)
{
    ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
    newElem->val = val;
    newElem->next = lst->head;

    lst->head = newElem;
    if (lst->length == 0)
    {
        lst->queue = newElem;
    }

    lst->length += 1;
}

void removeListNode(List *lst, int indx)
{
    ListNode *before = NULL;
    ListNode *current = lst->head;
    for (int i = 0; i < indx; i++)
    {
        before = current;
        current = current->next;
    }
    //
    // i = 0 whdha
    if (indx == 0)
    {
        lst->head = current->next;
    }
    // i = len - 1 whda

    //
    if (before != NULL)
    {
        before->next = current->next;
        if (indx == lst->length - 1)
        {
            lst->queue = before;
        }
    }
    free(current);

    lst->length -= 1;
}

void printList(List *lst)
{
    printf("[");
    ListNode *current = lst->head;
    for (int i = 0; i < lst->length; i++)
    {
        int *val = (int *)current->val;
        printf("%d ", *val);
        current = current->next;
    }
    printf("]");
}




typedef ListNode QueueNode;
typedef List Queue;

Queue *initQueue()
{
    return (Queue *)initList();
}

void pushQueueNode(Queue *lst, void *val)
{
    addListNode1(lst, val);
}

void *popQueueNode(Queue *lst)
{
    void *rslt = (void *)(lst->head->val);
    removeListNode(lst, 0);

    return rslt;
}

void printQueue(Queue *queue)
{
    char *seprator = "______________";
    printf("%s\n", seprator);
    //

    void *val;
    int len = queue->length;

    while (len > 0)
    {
        val = popQueueNode(queue);
        pushQueueNode(queue, val);
        printf("%p\n%s\n", val, seprator);
        len--;
    }
}





typedef ListNode StackNode;
typedef List Stack;

Stack *initStack()
{
    return (Stack *)initList();
}

void pushStackNode(Stack *stk, void *val)
{
    addListNode2(stk, val);
}

void *popStackNode(Stack *stk)
{
    void *rslt = (void *)(stk->head->val);
    removeListNode(stk, 0);

    return rslt;
}

void printStack(Stack *stk)
{
    printf("__\n");
    //
    Stack *tmp = initStack();
    void *val;
    int len = stk->length;

    while (len > 0)
    {
        val = popStackNode(stk);
        pushStackNode(tmp, val);
        printf("%p\n__\n", val);
        len--;
    }
    // refill
    len = tmp->length;
    while (len > 0)
    {
        val = popStackNode(tmp);
        pushStackNode(stk, val);

        len--;
    }

    free(tmp);
}

const int CLK = 500; // ms
#define iStackLength 3

#define iQueueLength 10


#include <time.h>
#define MaxProcCLK 20

int lastProcessId = 0;

typedef struct
{
    int id;
    char *arvTime;
    int clocks;
    float exeTime; // in s
    int size;
    int priority;

    SDL_Color color;
} Process;

int randomNum(int min, int max)
{
    return (rand() % (max - min)) + min;
}

Process *initProcess()
{
    Process *process = (Process *)malloc(sizeof(Process));

    // get the current time
    time_t currentTime;
    time(&currentTime);
    process->arvTime = (char *)ctime(&currentTime);
    // get the id
    process->id = lastProcessId;
    lastProcessId += 1;

    // set the clocks + exeTime
    process->clocks = randomNum(10, MaxProcCLK);
    process->exeTime = (float)((process->clocks) * CLK) / 1000; // in s

    // set the size
    process->size = randomNum(1, 6) * sizeof(Process);

    // set the priority
    process->priority = randomNum(0, iStackLength);

    // set a color
    process->color.r = randomNum(0, 255);
    process->color.g = randomNum(0, 255);
    process->color.b = randomNum(0, 255);
    process->color.a = 255;

    return process;
}

void pushProcessQueue(Queue *queue, Process *process)
{
    pushQueueNode(queue, process);
}

void killProcess(Process *process)
{
    free(process->arvTime);
    free(process);
}

void printProcess(Process *process)
{
    printf("# process%d (~%.1fs remaing)\n", process->id, process->exeTime);
}
typedef struct
{
    void *val;
} ArrayNode;

typedef struct
{
    ArrayNode *arr; // points the the first elem
    int length;
} Array;

Array *initArray()
{
    Array *arr = (Array *)malloc(sizeof(Array));
    arr->length = 0;
    arr->arr = NULL;
    return arr;
}

void pushArrayNode(Array *arr, void *val)
{
    arr->length += 1;

    if (arr->arr == NULL)
    {
        arr->arr = malloc(sizeof(ArrayNode));
    }
    else

    {
        arr->arr = realloc(arr->arr, arr->length * sizeof(ArrayNode));
    }

    ArrayNode new;
    new.val = val;

    arr->arr[arr->length - 1] = new;
}

void delArrayNode(Array *arr, int indx)
{
    for (int i = indx; i < arr->length - 1; i++)
    {
        arr->arr[i] = arr->arr[i + 1];
    }

    arr->length -= 1;
    arr->arr = realloc(arr->arr, (arr->length) * sizeof(ArrayNode));
}

void printArray(Array *arr)
{
    printf("[");

    for (int i = 0; i < arr->length; i++)
    {
        printf("%p", arr->arr[i].val);
        if (i < arr->length - 1)
        {
            printf(", ");
        }
    }

    printf("]\n");
}

void freeArray(Array *arr)
{
    int length = arr->length;
    for (int i = 0; i < length; i++)
    {
        free(arr->arr[i].val);
    }
    free(arr->arr);
    free(arr);
}
int partitionId = 0;

typedef struct partition
{
    int size;
    bool occupied;
    Array *startAdr;
    int id;
} Partition;

Partition *initPartition(int size)
{
    Partition *partition = (Partition *)malloc(sizeof(partition));
    partition->size = size;
    partition->occupied = false;
    partition->startAdr = initArray();

    partition->id = partitionId;
    partitionId += 1;

    return partition;
}

void pushProcess(Partition *partition, Process *process)
{
    pushArrayNode(partition->startAdr, process);
}

void printPartition(Partition *partition)
{
    printf("------partition %d------\n", partition->id);
    printf("size: %d Bytes\n\n", partition->size);
    

    Array *processes = partition->startAdr;
    Process *currentProcess;

    for (int i = 0; i < processes->length; i++)
    {
        currentProcess = (Process *)processes->arr[i].val;
        printProcess(currentProcess);
    }

    printf("-----------------------\n\n");
}
const int ramSize = 1024; // 1KB

typedef struct
{
    int freeSpace; // for partitions
    List *partitions;
} Ram;

Ram *initRam()
{
    Ram *ram = (Ram *)malloc(sizeof(Ram));
    ram->freeSpace = ramSize;
    ram->partitions = initList();

    // create the partitions
    Partition *partition;
    for (int i = 0; i < 4; i++)
    {
        partition = initPartition(ramSize / 4);
        addListNode1(ram->partitions, partition);
        ram->freeSpace -= ramSize / 4;
    }

    return ram;
}

int loadProcess(Ram *ram, Process *process, int strategy)
{
    ListNode *current;
    Partition *crntPart;

    int difference;

    switch (strategy)
    {
    case 0: // first fit
        current = ram->partitions->head;
        while (current)
        {
            crntPart = (Partition *)current->val;
            if (!crntPart->occupied)
            {
                if (crntPart->size >= process->size)
                {
                    pushArrayNode(crntPart->startAdr, process);
                    crntPart->occupied = true;

                    // create a new partition
                    difference = crntPart->size - process->size;
                    if (difference > 0)
                    {
                        crntPart->size = process->size;

                        crntPart = initPartition(difference);
                        addListNode1(ram->partitions, crntPart);
                    }

                    return 1;
                }
            }
            current = current->next;
        }

        break;
    case 1: // best fit
        difference = 0;
        // get hte largest partition  first the init the difference with it
        current = ram->partitions->head;
        while (current)
        {
            crntPart = current->val;
            if (crntPart->size > difference)
            {
                difference = crntPart->size;
            }

            current = current->next;
        }

        // get the difference
        int bestIndx = -1;
        current = ram->partitions->head;
        for (int i = 0; i < ram->partitions->length; i++)
        {
            crntPart = current->val;
            if (!crntPart->occupied)
            {
                if (crntPart->size - process->size < difference)
                {
                    difference = crntPart->size - process->size;
                    bestIndx = i;
                }
            }

            current = current->next;
        }

        // load the process
        if (bestIndx > -1) // something was found
        {
            current = ram->partitions->head;
            while (current)
            {
                crntPart = current->val;
                if (!bestIndx)
                {
                    // load
                    pushArrayNode(crntPart->startAdr, process);
                    crntPart->occupied = true;

                    // create a new partition

                    if (difference > 0)
                    {
                        crntPart->size = process->size;

                        crntPart = initPartition(difference);
                        addListNode1(ram->partitions, crntPart);
                    }

                    return 1;
                }

                bestIndx -= 1;
                current = current->next;
            }
        }

        break;
    case 2: // worst fit
        difference = 0;
        int worstIndx = -1;

        // get the difference
        current = ram->partitions->head;
        for (int i = 0; i < ram->partitions->length; i++)
        {
            crntPart = current->val;
            if (!crntPart->occupied)
            {
                if (crntPart->size - process->size > difference)
                {
                    difference = crntPart->size - process->size;
                    worstIndx = i;
                }
            }

            current = current->next;
        }

        // load the process
        if (worstIndx > -1) // something was found
        {
            current = ram->partitions->head;
            while (current)
            {
                crntPart = current->val;
                if (!worstIndx)
                {
                    // load
                    pushArrayNode(crntPart->startAdr, process);
                    crntPart->occupied = true;

                    // create a new partition

                    if (difference > 0)
                    {
                        crntPart->size = process->size;

                        crntPart = initPartition(difference);
                        addListNode1(ram->partitions, crntPart);
                    }

                    return 1;
                }

                worstIndx -= 1;
                current = current->next;
            }
        }

        break;
    default:
        break;
    }

    return 0;
}

int tickRam(Ram *ram) // returns if something was deleted
{
    bool deleted = false;
    // tick processes
    ListNode *current = ram->partitions->head;
    Partition *currentPartition;
    Array *currentProcesses;
    Process *currentProcess;

    while (current)
    {
        currentPartition = (Partition *)current->val;
        currentProcesses = (Array *)currentPartition->startAdr;
        for (int i = 0; i < currentProcesses->length; i++)
        {
            currentProcess = (Process *)currentProcesses->arr[i].val;
            currentProcess->clocks -= 1;
            currentProcess->exeTime -= (float)CLK / 1000;
        }

        current = current->next;
    }
    // delete completed processes
    current = ram->partitions->head;
    while (current)
    {
        currentPartition = (Partition *)current->val;
        currentProcesses = (Array *)currentPartition->startAdr;
        for (int i = 0; i < currentProcesses->length; i++)
        {
            currentProcess = (Process *)currentProcesses->arr[i].val;
            if (!currentProcess->clocks)
            {
                // delete the proces
                delArrayNode(currentProcesses, i);
                i -= 1;
                deleted = true;
                // free partition
                if (!currentProcesses->length)
                {
                    currentPartition->occupied = false;
                }
            }
        }

        current = current->next;
    }
    return deleted;
}

// merge randomly
int mergePartitions(Ram *ram) // returns  merged
{

    List *partitions = ram->partitions;
    ListNode *current = partitions->head;

    Partition *currentPartition;
    int freeNum = 0;

    // get freeNum
    while (current)
    {
        currentPartition = (Partition *)current->val;
        if (!currentPartition->occupied)
        {
            freeNum += 1;
        }

        current = current->next;
    }

    //
    current = partitions->head;

    Partition *toDel;
    int toDelIndx;

    if (freeNum > 1)
    {
        // get the one to free
        for (int i = 0; i < partitions->length; i++)
        {

            currentPartition = (Partition *)current->val;
            if (!currentPartition->occupied)
            {
                toDel = currentPartition;
                toDelIndx = i;
                break;
            }

            current = current->next;
        }

        // merge
        current = partitions->head;
        for (int i = 0; i < partitions->length; i++)
        {

            currentPartition = (Partition *)current->val;

            if (!currentPartition->occupied)
            {
                if (i != toDelIndx)
                {
                    // merge toDel with the current
                    currentPartition->size += toDel->size;
                    // delete to del
                    freeArray(toDel->startAdr);
                    removeListNode(partitions, toDelIndx);

                    // break;
                    return 1;
                }
            }

            current = current->next;
        }
    }
    return 0;
}

void printRam(Ram *ram)
{
    printf("__________RAM__________\n\n");

    ListNode *currentPart = ram->partitions->head;

    while (currentPart)
    {
        printPartition(currentPart->val);

        currentPart = currentPart->next;
    }

    printf("_______________________\n\n\n");
}

#include <strings.h>

typedef struct
{
    char *text;
    TTF_Font *font;
    SDL_Color color;
    SDL_Texture *texture;
    SDL_Rect *rect;
} Text;

Text *createText(SDL_Renderer *renderer, TTF_Font *font, char *fontPath, int fontSize, char *text, SDL_Color fgClr, int x, int y)
{
    if (font == NULL)
    {
        font = TTF_OpenFont(fontPath, fontSize);
    }

    char *text2 = text;
    if (text2[0] == *"\0")
    {
        text2 = " ";
    }

    Text *widget = (Text *)malloc(sizeof(Text));
    widget->text = text;
    widget->color = fgClr;
    widget->font = font;
    widget->rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));

    SDL_Surface *surface = TTF_RenderText_Solid(font, text2, fgClr);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    widget->rect->x = x;
    widget->rect->y = y;
    widget->rect->w = surface->w;
    widget->rect->h = surface->h;
    widget->texture = texture;

    return widget;
}

void drawText(SDL_Renderer *renderer, Text *text)
{
    SDL_RenderCopy(renderer, text->texture, NULL, text->rect);
    // SDL_DestroyTexture(text->texture);
}

void updateText(SDL_Renderer *renderer, Text *widget, char *text)
{
    char *text2 = text;
    if (text2[0] == *"\0")
    {
        text2 = " ";
    }

    if (strcmp(text2, widget->text))
    {
        
        
        //free(widget->text);

        widget->text = text2;

        SDL_Surface *surface = TTF_RenderText_Solid(widget->font, text2, widget->color);
        SDL_DestroyTexture(widget->texture);
        widget->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        widget->rect->w = surface->w;
        widget->rect->h = surface->h;
    }
}

void eraseText(Text *txt)
{
    SDL_DestroyTexture(txt->texture);
    free(txt->rect);
    free(txt->text);
    free(txt);
}

void changeTextColor(Text *widget, SDL_Color color)
{
    widget->color = color;
}
#define LegendsNum 9

char *legends[LegendsNum] = {"<q> toggle processor",
                             "<w> toggle queue",
                             "<e> first fit",
                             "<r> best fit",
                             "<t> worst fit",
                             "<y> toggle priority",
                             "<u> toggle sound",
                             "",
                             "<Esc> exit"};

const int legendPadding = 10;
TTF_Font *legendFont;

typedef struct
{
    SDL_Rect *mainRect;
    Text *txt[LegendsNum];

} WidgetLegend;

WidgetLegend *initLengendW(SDL_Renderer *renderer)
{
    legendFont = TTF_OpenFont("assets/fonts/QuickSand.ttf", 15);
    WidgetLegend *legend = (WidgetLegend *)malloc(sizeof(WidgetLegend));

    // create text
    int previousY = 0;

    int mainRectW = 0;
    int mainRectH = 0;

    Text *txt;
    for (int i = 0; i < LegendsNum; i++)
    {
        txt = createText(renderer, legendFont, NULL, 0, legends[i], WHITECLR, 0, 0);

        legend->txt[i] = txt;
        txt->rect->y = previousY;
        previousY += txt->rect->h;
        // calc rect dims
        mainRectH += txt->rect->h;
        // get max width
        if (txt->rect->w > mainRectW)
        {
            mainRectW = txt->rect->w;
        }
    }

    // create rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->h = mainRectH + 2 * legendPadding;
    mainRect->w = mainRectW + 2 * legendPadding;
    mainRect->x = SCREEN_WIDTH - (mainRect->w + MAINPADDING);
    mainRect->y = SCREEN_HEIGHT - (mainRect->h + MAINPADDING);

    legend->mainRect = mainRect;

    // text postion
    for (int i = 0; i < LegendsNum; i++)
    {
        txt = legend->txt[i];
        txt->rect->x += mainRect->x + legendPadding;
        txt->rect->y += mainRect->y + legendPadding;
    }

    return legend;
}

void drawLegendW(SDL_Renderer *renderer, WidgetLegend *widget)
{

    // draw rect
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);
    SDL_RenderDrawRect(renderer, widget->mainRect);

    // draw text
    for (int i = 0; i < LegendsNum; i++)
    {
        drawText(renderer, widget->txt[i]);
    }
}
typedef struct
{
    SDL_Color color;
    SDL_Rect *mainRect;
    Text *szTxt;

    int id;
    Text *idTxt;
    Text *clkTxt;
} WidgetProcess;

#define txtPadding 5

TTF_Font *processFont;

WidgetProcess *initProcessW(SDL_Renderer *renderer, Process *process, int width, int height, int x, int y)
{
    WidgetProcess *widget = (WidgetProcess *)malloc(sizeof(WidgetProcess));
    widget->id = process->id;
    // font
    if (processFont == NULL)
    {
        processFont = TTF_OpenFont("assets/fonts/QuickSand.ttf", 10);
    }

    // color
    widget->color.r = process->color.r;
    widget->color.g = process->color.g;
    widget->color.b = process->color.b;
    widget->color.a = process->color.a;

    // main Rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->x = x;
    mainRect->y = y;
    mainRect->w = width;
    mainRect->h = height;

    widget->mainRect = mainRect;

    // id text

    char *idVal = (char *)malloc(10);
    sprintf(idVal, "%d", process->id);
    Text *idText = createText(renderer, processFont, NULL, 0, idVal, widget->color, x + txtPadding, y + txtPadding);
    widget->idTxt = idText;

    // size text

    char *sizeVal = (char *)malloc(10);
    sprintf(sizeVal, "%dB", process->size);
    Text *sizeText = createText(renderer, processFont, NULL, 0, sizeVal, widget->color, x, y);
    sizeText->rect->x += mainRect->w - sizeText->rect->w - txtPadding;
    sizeText->rect->y += mainRect->h - sizeText->rect->h - txtPadding;
    widget->szTxt = sizeText;

    // clock text
    char *clkVal = (char *)malloc(10);
    sprintf(clkVal, "%dC", process->clocks);
    Text *clkText = createText(renderer, processFont, NULL, 0, clkVal, widget->color, x, y);
    clkText->rect->x += txtPadding;
    clkText->rect->y += mainRect->h - sizeText->rect->h - txtPadding;
    widget->clkTxt = clkText;

    return widget;
}

void drawProcessW(SDL_Renderer *renderer, WidgetProcess *process)
{
    // draw body
    SDL_SetRenderDrawColor(renderer, process->color.r,
                           process->color.g,
                           process->color.b,
                           process->color.a);
    SDL_RenderDrawRect(renderer, process->mainRect);

    // draw text
    drawText(renderer, process->idTxt);
    drawText(renderer, process->szTxt);
    drawText(renderer, process->clkTxt);
}

void eraseProcessW(WidgetProcess *process)
{
    free(process->mainRect);
    eraseText(process->idTxt);
    eraseText(process->szTxt);
    eraseText(process->clkTxt);
    free(process);
}
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

WidgetLegend *legendW;
WidgetIStack *iStackW;

#define StatusNum 7

char *statusVals[StatusNum] = {
    "processor ",
    "queue ",
    "first fit ",
    "best fit ",
    "worst fit ",
    "priority",
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

void updateStatusW(SDL_Renderer *renderer, WidgetStatus *widget, bool processor, bool queue, bool stategy, int priority, bool sound)
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
    for (int i = 0; i < 3; i++)
    {
        if (i == stategy)
        {
            changeTextColor(widget->vals[i + 2], GREENCLR);
            updateText(renderer, widget->vals[i + 2], "<on>");
        }
        else
        {
            changeTextColor(widget->vals[i + 2], REDCLR);
            updateText(renderer, widget->vals[i + 2], "<off>");
        }
    }

    // priority
    if (priority)
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

const int partnPdng = 10;

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
    if (widget->processW->length)
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
    ListNode *current = widget->processW->head;
    while (current)
    {
        drawProcessW(renderer, current->val);
        current = current->next;
    }

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
    // mainRect->x = MAINPADDING * 2 + SCREEN_WIDTH / 10;
    mainRect->x = iStackW->mainRect->x + iStackW->mainRect->w + MAINPADDING;
    mainRect->y = MAINPADDING;
    mainRect->w = SCREEN_WIDTH - mainRect->x - MAINPADDING;
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

    // calc dims
    int pW = (widget->grpRect->w - (ram->partitions->length + 1) * MAINPADDING) / ram->partitions->length;
    if (pW > SCREEN_WIDTH / 10)
    {
        pW = SCREEN_WIDTH / 10;
    }
    int pH = widget->grpRect->h - MAINPADDING * 2;

    int x = widget->grpRect->x + (widget->grpRect->w - (pW + MAINPADDING) * ram->partitions->length + MAINPADDING) / 2;
    int y = widget->grpRect->y + MAINPADDING;

    // create the partitions
    current = ram->partitions->head;
    WidgetPartition *partitionW;
    float ratio;

    for (int i = 0; i < ram->partitions->length; i++)
    {

        if (maxSize)
        {
            ratio = (float)((Partition *)(current->val))->size / maxSize;
        }
        else
        {
            ratio = 0;
        }

        partitionW = initPartitionW(renderer, current->val, pW, pH * ratio, x + i * pW + (i)*MAINPADDING, y);
        addListNode1(widget->partitionsW, partitionW);
        current = current->next;
    }
}

Window *window;
SDL_Renderer *renderer;

// Queue *iQueue;      // instruction queue
Stack *iStack;      // iQueue Stack
Ram *ramPartitions; // ram

// WidgetIQueue *iQueueW;

WidgetRam *ramW;

WidgetStatus *statusW;

bool runProcessor = false;
bool runQueue = false;

int loadingStrategy = 0; /*first f best f worst f*/
bool priority = false;
bool sound = true;
#include "SDL2/SDL_mixer.h"
#define soundsNum 4


char *soundsPaths[soundsNum] = {"assets/sounds/start1.mp3", "assets/sounds/stop1.mp3", "assets/sounds/start2.mp3", "assets/sounds/stop2.mp3"};
Mix_Music *sounds[soundsNum];

void initSounds()
{
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640); // open the device

    for (int i = 0; i < soundsNum; i++)
    {
        sounds[i] = Mix_LoadMUS(soundsPaths[i]);
    }
}

void playSound(int soundId, bool canPlay)
{
    if (canPlay)
    {
        Mix_PlayMusic(sounds[soundId], 0);
    }
}
void eventFunc(SDL_Event e)
{
    // keyboard events
    if (e.type == SDL_KEYDOWN)
    {

        switch (e.key.keysym.sym)
        {

        case 113: // q
            runProcessor = !runProcessor;
            break;
        case 119: // w
            runQueue = !runQueue;
            break;
        case 101: // e first
            loadingStrategy = 0;
            break;
        case 114: // r best
            loadingStrategy = 1;
            break;
        case 116: // t worst
            loadingStrategy = 2;
            break;
        case 121: // y
            priority = !priority;
            break;

        case 117: // u
            sound = !sound;
            break;

        default:
            break;
        }
    }
}
int currentNodeIndx;
Stack *tmpStack;
Queue *currentQueue;

Process *currentProcess;

int counter = CLK / REFRESHRATE;

void loopFunc(Window *window)
{
    if (counter >= CLK / REFRESHRATE)
    {

        // add processes to iQueue
        if (runQueue)
        {
            tmpStack = initStack();
            currentNodeIndx = 0;
            while (iStack->length)
            {
                currentQueue = popStackNode(iStack);
                pushStackNode(tmpStack, currentQueue);

                // get an empty queue
                if (currentQueue->length < iQueueLength)
                {
                    currentProcess = initProcess();
                    currentProcess->priority = currentNodeIndx;
                    pushQueueNode(currentQueue, currentProcess);

                    break;
                }
                currentNodeIndx += 1;
            }

            // refiil everything
            while (tmpStack->length)
            {
                pushStackNode(iStack, popStackNode(tmpStack));
            }

            free(tmpStack);
        }

        // processor

        if (runProcessor)
        {
            if (tickRam(ramPartitions)) // if a process if completed
            {
                playSound(3, sound);
            }
            else
            {
                playSound(1, sound); // if this is a normal tick
            }

            tmpStack = initStack();
            while (iStack->length)
            {
                currentQueue = popStackNode(iStack);
                pushStackNode(tmpStack, currentQueue);

                if (currentQueue->length)
                {
                    currentProcess = (Process *)popQueueNode(currentQueue);
                    // load process
                    if (!loadProcess(ramPartitions, currentProcess, loadingStrategy))
                    {
                        pushQueueNode(currentQueue, currentProcess);
                    }
                    else
                    {
                        playSound(2, sound); // start execution
                    }

                    if (priority)
                    {
                        break;
                    }
                }
            }
            // refill everything
            while (tmpStack->length)
            {
                pushStackNode(iStack, popStackNode(tmpStack));
            }

            free(tmpStack);

            // merge after the new process takes an empty partition

            if (mergePartitions(ramPartitions)) // if merged
            {
                playSound(0, sound); // if this is a normal tick
            };
        }

        // print the ram
        // printRam(ramPartitions);

        // refresh
        SDL_SetRenderDrawColor(window->renderer, BGCLR.r, BGCLR.g, BGCLR.b, BGCLR.a);
        SDL_RenderClear(window->renderer);
        //

        // updateWIQueue(renderer, iQueueW, iQueue);
        // drawWIQueue(renderer, iQueueW);

        updateWIStack(renderer, iStackW, iStack);
        drawWIStack(renderer, iStackW);

        updateRawW(renderer, ramW, ramPartitions);
        drawRawW(renderer, ramW);

        updateStatusW(renderer, statusW, runProcessor, runQueue, loadingStrategy, priority, sound);
        drawStatusW(renderer, statusW);

        drawLegendW(renderer, legendW);
        //
        SDL_RenderPresent(window->renderer);
        counter = 0;
    }

    counter++;
}


int main(int argc, char *args[])
{
    srand(time(NULL)); // set the seed

    window = initWin("memSym");
    pixelFormat = SDL_GetWindowSurface(window->win)->format;
    renderer = window->renderer;
    MAINPADDING *= window->padding;

    // structs inits
    iStack = initStack();
    for (int i = 0; i < iStackLength; i++)
    {
        pushStackNode(iStack, initQueue());
    }

    ramPartitions = initRam();

    // widgets inits
    legendW = initLengendW(renderer);
    statusW = initStatusW(renderer);

    iStackW = initWIStack();
    ramW = initRamW();
    
    //init sound
    initSounds();


    mainLoop(window, eventFunc, loopFunc);

    return 0;
}