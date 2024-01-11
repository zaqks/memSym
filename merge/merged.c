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
typedef struct listNode
{
    void *val;
    struct listNode *next;
} ListNode;

typedef struct
{
    ListNode *head;
} List;

int getListLengthRec(ListNode *head, int indx)
{
    if (!head)
    {
        return indx;
    }
    getListLengthRec(head->next, indx + 1);
}

ListNode *getListQueueRec(ListNode *head)
{
    if (!head->next)
    {
        return head;
    }
    getListQueueRec(head->next);
}

void printListRec(ListNode *head)
{
    if (head)
    {
        printf("%p ", head->val);
        printListRec(head->next);
    }
}
List *initList()
{
    List *lst = (List *)malloc(sizeof(List));
    lst->head = NULL;
}

int getListLength(List *lst)
{
    return getListLengthRec(lst->head, 0);
}

ListNode *getListQueue(List *lst)
{
    return getListQueueRec(lst->head);
}

// queue mode
void addListNode1(List *lst, void *val)
{
    ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
    newElem->val = val;
    newElem->next = NULL;

    if (!lst->head)
    {
        lst->head = newElem;
    }
    else
    {
        // find the last one
        ListNode *current = lst->head;
        getListQueue(lst)->next = newElem;
    }
}
// stack mode
void addListNode2(List *lst, void *val)
{
    ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
    newElem->val = val;
    newElem->next = lst->head;

    lst->head = newElem;
}

int removeListNode(List *lst, int indx)
{
    if (indx < getListLength(lst))
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
        if (!indx)
        {
            lst->head = current->next;
        }
        // i = len - 1 whda

        //
        if (before)
        {
            before->next = current->next;
        }
        free(current);
        return 1;
    }
    printf("invalid indx\n");
    return 0;
}

void printList(List *lst)
{
    printf("[");
    printListRec(lst->head);
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

int queueLength(Queue *queue)
{
    return getListLength(queue);
}

int emptyQueue(Queue *queue)
{
    return !getListLength(queue);
}

void printQueue(Queue *queue)
{
    char *seprator = "______________";
    printf("%s\n", seprator);
    //

    void *val;
    for (int i = 0; i < queueLength(queue); i++)
    {
        val = popQueueNode(queue);
        pushQueueNode(queue, val);
        printf("%p\n%s\n", val, seprator);
    }
}



typedef ListNode StackNode;
typedef List Stack;

Stack *initStack()
{
    return (Stack *)initList();
}

int stackLength(Stack *stk)
{
    return getListLength(stk);
}

int emptyStack(Stack *stk)
{
    return !getListLength(stk);
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

    while (!emptyStack(stk))
    {
        val = popStackNode(stk);
        pushStackNode(tmp, val);
        printf("%p\n__\n", val);
    }
    // refill
    while (!emptyStack(tmp))
    {
        pushStackNode(stk, popStackNode(tmp));
    }

    free(tmp);
}

#define CLK  250 // ms

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
    if (process->clocks > 0)
    {
        printf("# process%d (~%.1fs remaing) lvl%d since:%s\n", process->id, process->exeTime, process->priority, process->arvTime);
    }
    else
    {
        printf("# process%d infinite lvl%d since:%s\n", process->id, process->priority, process->arvTime);
    }
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
int ramSize = 1024; // 1KB

typedef struct
{
    // int freeSpace; // for partitions
    List *partitions;
} Ram;

Ram *initRam()
{
    Ram *ram = (Ram *)malloc(sizeof(Ram));
    // ram->freeSpace = ramSize;
    ram->partitions = initList();

    // create the partitions
    Partition *partition;
    int partitionsNum = randomNum(3, 7);
    int freeSpace = ramSize;
    for (int i = 0; i < partitionsNum; i++)
    {
        partition = initPartition(ramSize / partitionsNum);
        addListNode1(ram->partitions, partition);
        freeSpace -= ramSize / partitionsNum;
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
        for (int i = 0; i < getListLength(ram->partitions); i++)
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
        for (int i = 0; i < getListLength(ram->partitions); i++)
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

            if (currentProcess->clocks > 0)
            {
                currentProcess->clocks -= 1;
                currentProcess->exeTime -= (float)CLK / 1000;
            }
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
        for (int i = 0; i < getListLength(ram->partitions); i++)
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
        for (int i = 0; i < getListLength(ram->partitions); i++)
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

void printIQueue(Queue *queue)
{
    Process *current;
    for (int i = 0; i < queueLength(queue); i++)
    {
        current = popQueueNode(queue);
        pushQueueNode(queue, current);

        printProcess(current);
    }
}

void printIStack(Stack *stk)
{

    printf("________iSTACK_________\n\n");

    Stack *tmpStk = initStack();

    Queue *current;
    for (int i = 0; !emptyStack(stk); i++)
    {
        printf("--queue%d--------------\n", i);

        current = popStackNode(stk);
        pushStackNode(tmpStk, current);

        printIQueue(current);

        printf("----------------------\n");
    }

    while (!emptyStack(tmpStk))
    {
        pushStackNode(stk, popStackNode(tmpStk));
    }

    free(tmpStk);
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
typedef struct
{
    int x1;
    int y1;
    int w;
    int h;
    int x3;
    int y3;

} Parallelogram;

Parallelogram *initParallelogram(int x1,
                                 int y1,
                                 int w,
                                 int h,
                                 int x3,
                                 int y3)
{
    Parallelogram *shape = (Parallelogram *)malloc(sizeof(Parallelogram));

    shape->x3 = x3;
    shape->y3 = y3;

    shape->x1 = x1;
    shape->y1 = y1;
    shape->w = w;
    shape->h = h;

    

    return shape;
}

void drawParallelogram(SDL_Renderer *renderer, Parallelogram *shape, bool fill)
{

    int x2 = shape->x1 + shape->w + shape->x3;
    int y2 = shape->y1 + shape->h + shape->y3;

    // fill
    if (fill)
    {
      

        int dx1;
        int dy1;
        int dx2;
        int dy2;

        if (shape->x3)
        {
            x2 = shape->x1 + shape->x3;
            y2 = shape->y1 + shape->h + shape->y3;

            dx1 = shape->x1;
            dy1 = shape->y1;
            dx2 = x2;
            dy2 = y2;

            for (int i = 0; i < shape->w; i++)
            {
                SDL_RenderDrawLine(renderer, dx1, dy1, dx2, dy2);

                dx1 += 1;
                dx2 += 1;
            }
        }
        else
        {
            if (shape->y3)
            {
                dx1 = shape->x1;
                dy1 = shape->y1;
                dx2 = x2;
                dy2 = dy1 + shape->y3;

                for (int i = 0; i < shape->h; i++)
                {
                    SDL_RenderDrawLine(renderer, dx1, dy1, dx2, dy2);

                    dy1 += 1;
                    dy2 += 1;
                }
            }
        }
    }
    else
    {
        int lines[4][4] =
            {
                {shape->x1, shape->y1, x2 - shape->x3, shape->y1 + shape->y3}, // 1
                {x2 - shape->x3, shape->y1 + shape->y3, x2, y2},               // 2
                {shape->x1 + shape->x3, y2 - shape->y3, x2, y2},               // 3
                {shape->x1, shape->y1, shape->x1 + shape->x3, y2 - shape->y3}, // 4
            };

        for (int i = 0; i < 4; i++)
        {
            SDL_RenderDrawLine(renderer, lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
        }
    }
}

 
#define LegendsNum 10

char *legends[LegendsNum] = {"<q> toggle processor",
                             "<w> toggle queue",
                             "<e> first fit",
                             "<r> best fit",
                             "<t> worst fit",
                             "<y> toggle priority",
                             "<u> toggle print mode",
                             "<i> toggle sound",
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
    Parallelogram *face1;
    Parallelogram *face2;

    Text *szTxt;
    Text *clkTxt;
    Text *priorityTxt;

    int id;
    Text *idTxt;

    Array *levels;

} WidgetProcess;

#define txtPadding 5

#define beta 45

#define maxProcZ 50


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

    // 3d faces

    // face2
    // double b = atan((double)width / height);

    double zH = maxProcZ;
    if (process->clocks > 1)
    {
        zH *= ((double)process->clocks / MaxProcCLK);
    }

    Parallelogram *face2 = initParallelogram(x, y, zH * sin(beta), height, 0, -zH * cos(beta));
    widget->face2 = face2;

    mainRect->x += face2->w;
    mainRect->y += face2->y3;
    // face1
    Parallelogram *face1 = initParallelogram(x + face2->w, y + face2->h + face2->y3, width, zH * cos(beta), -face2->w, 0);
    widget->face1 = face1;

    // levels
    widget->levels = initArray();
    if (process->clocks > 0)
    {
        Parallelogram *currentLevel;

        for (int i = 1; i < process->clocks + 1; i++)
        {
            // face2
            currentLevel = initParallelogram(
                face2->x1,
                face2->y1,
                face2->w * i / process->clocks,
                face2->h,
                face2->x3,
                face2->y3 * i / process->clocks);

            pushArrayNode(widget->levels, currentLevel);

            /*
            // face1
            currentLevel = initParallelogram(
                face1->x1,
                face1->y1,
                face1->w,
                face1->h * i / (process->clocks),
                face1->x3 * i / (process->clocks),
                face1->y3);

            pushArrayNode(widget->levels, currentLevel);
            */
        }
    }

    // id text

    char *idVal = (char *)malloc(10);
    sprintf(idVal, "%d", process->id);
    Text *idText = createText(renderer, processFont, NULL, 0, idVal, widget->color, mainRect->x + txtPadding, mainRect->y + txtPadding);
    widget->idTxt = idText;

    // size text

    char *sizeVal = (char *)malloc(10);
    sprintf(sizeVal, "%dB", process->size);
    Text *sizeText = createText(renderer, processFont, NULL, 0, sizeVal, widget->color, mainRect->x, mainRect->y);
    sizeText->rect->x += mainRect->w - sizeText->rect->w - txtPadding;
    sizeText->rect->y += mainRect->h - sizeText->rect->h - txtPadding;
    widget->szTxt = sizeText;

    // clock text
    char *clkVal = (char *)malloc(10);
    sprintf(clkVal, "%dC", process->clocks);
    Text *clkText = createText(renderer, processFont, NULL, 0, clkVal, widget->color, mainRect->x, mainRect->y);
    clkText->rect->x += txtPadding;
    clkText->rect->y += mainRect->h - sizeText->rect->h - txtPadding;
    widget->clkTxt = clkText;

    // priotrity text
    char *prVal = (char *)malloc(2);
    sprintf(prVal, "%d", process->priority);

    Text *prText = createText(renderer, processFont, NULL, 0, prVal, widget->color, mainRect->x, idText->rect->y);
    prText->rect->x += mainRect->w - prText->rect->w - txtPadding;
    widget->priorityTxt = prText;

    return widget;
}

void drawProcessW(SDL_Renderer *renderer, WidgetProcess *process)
{

    // draw 3d faces
    SDL_SetRenderDrawColor(renderer, process->color.r,
                           process->color.g,
                           process->color.b,
                           process->color.a);
    drawParallelogram(renderer, process->face1, true);
    drawParallelogram(renderer, process->face2, true);

    // draw facing area
    SDL_SetRenderDrawColor(renderer, BGCLR.r,
                           BGCLR.g,
                           BGCLR.b,
                           BGCLR.a);
    SDL_RenderFillRect(renderer, process->mainRect);
    SDL_RenderDrawRect(renderer, process->mainRect);

    // draw levels

    for (int i = 0; i < process->levels->length; i++)
    {
        drawParallelogram(renderer, process->levels->arr[i].val, 0);
    }

    // draw outlines
    SDL_SetRenderDrawColor(renderer, WHITECLR.r,
                           WHITECLR.g,
                           WHITECLR.b,
                           WHITECLR.a);

    drawParallelogram(renderer, process->face2, 0);
    drawParallelogram(renderer, process->face1, 0);
    SDL_RenderDrawRect(renderer, process->mainRect);

    // draw text
    drawText(renderer, process->idTxt);
    drawText(renderer, process->szTxt);
    drawText(renderer, process->clkTxt);
    drawText(renderer, process->priorityTxt);
}

void eraseProcessW(WidgetProcess *process)
{
    free(process->mainRect);
    free(process->face1);
    free(process->face2);

    freeArray(process->levels);

    eraseText(process->idTxt);
    eraseText(process->szTxt);
    eraseText(process->clkTxt);
    eraseText(process->priorityTxt);
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
    for (int i = widget->processesNum; i > 0; i--)
    {
        drawProcessW(renderer, widget->processesW[i - 1]);
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
    for (int i = 0; i < queueLength(queue); i++)
    {
        processRect = widget->processesRects[i]; // border
        current = (Process *)popQueueNode(queue);
        pushQueueNode(queue, current);
        widget->processesW[i] =
            initProcessW(renderer, current, processRect->w, processRect->h, processRect->x, processRect->y);
    }
    widget->processesNum = queueLength(queue);
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

    for (int i = iStackLength; i > 0; i--)
    {
        drawWIQueue(renderer, widget->queuesW[i - 1]);
    }
}

void updateWIStack(SDL_Renderer *renderer, WidgetIStack *widget, Stack *stack)
{
    Stack *tmpStack = initStack();
    //
    Queue *currentQueue;
    int currentNodeIndx = 0;
    while (stackLength(stack))
    {
        currentQueue = popStackNode(stack);
        pushStackNode(tmpStack, currentQueue);

        updateWIQueue(renderer, widget->queuesW[currentNodeIndx], currentQueue);

        currentNodeIndx += 1;
    }

    // refill
    while (stackLength(tmpStack))
    {
        pushStackNode(stack, popStackNode(tmpStack));
    }
    free(tmpStack);
}

WidgetLegend *legendW;
WidgetIStack *iStackW;
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
    Stack *toDraw = initStack();

    ListNode *current = widget->partitionsW->head;
    
    while (current)
    {
        pushStackNode(toDraw, current->val);
        current = current->next;
    }

    while (!emptyStack(toDraw))
    {
        drawPartitionW(renderer, popStackNode(toDraw));
    }

    free(toDraw);
}

void updateRawW(SDL_Renderer *renderer, WidgetRam *widget, Ram *ram)
{
    // delete partitionsW
    ListNode *currentW = widget->partitionsW->head;

    while (getListLength(widget->partitionsW))
    {
        erasePartitionW(currentW->val);
        currentW = currentW->next;
        removeListNode(widget->partitionsW, 0);
    }

    // get the max size
    int maxSize = 0;
    ListNode *current = ram->partitions->head;

    for (int i = 0; i < getListLength(ram->partitions); i++)
    {
        if (maxSize < ((Partition *)(current->val))->size)
        {
            maxSize = ((Partition *)(current->val))->size;
        }

        current = current->next;
    }

    // calc dims
    int pW = (widget->grpRect->w - (getListLength(ram->partitions) + 1) * MAINPADDING) / getListLength(ram->partitions);
    if (pW > SCREEN_WIDTH / 10)
    {
        pW = SCREEN_WIDTH / 10;
    }
    int pH = widget->grpRect->h - MAINPADDING * 2;

    int x = widget->grpRect->x + (widget->grpRect->w - (pW + MAINPADDING) * getListLength(ram->partitions) + MAINPADDING) / 2;
    int y = widget->grpRect->y + MAINPADDING;

    // create the partitions
    current = ram->partitions->head;
    WidgetPartition *partitionW;
    float ratio;

    for (int i = 0; i < getListLength(ram->partitions); i++)
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
int printIndx = 0;
#include "SDL2/SDL_mixer.h"
#define soundsNum 4


char *soundsPaths[soundsNum] = {"assets/sounds/start1.wav", "assets/sounds/stop1.wav", "assets/sounds/start2.wav", "assets/sounds/stop2.wav"};
Mix_Chunk *sounds[soundsNum];

void initSounds()
{
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // open the device

    for (int i = 0; i < soundsNum; i++)
    {
        sounds[i] = Mix_LoadWAV(soundsPaths[i]);
    }
}

void playSound(int soundId, bool canPlay)
{
    if (canPlay)
    {
        Mix_PlayChannel(-1, sounds[soundId], 0);
        //Mix_PlayMusic(sounds[soundId], 0);
    }
}
#include <assert.h>
const char *udPath = "data/userdata";

char **str_split(char *a_str, const char a_delim)
{
    char **result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char *) * count);

    if (result)
    {
        size_t idx = 0;
        char *token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int clk;
int newRamSz;
int stacks;
int queueL;

List *partsizes;
List *queueLens;
List *processes;

int getUserData()
{

    FILE *file;
    char *line = NULL;
    size_t len = 0;
    __ssize_t read;

    file = fopen(udPath, "r");
    if (!file)
    {
        return 0;
    }

    partsizes = initList();
    queueLens = initList();
    processes = initList();

    char **tokens;
    List *queueLens2 = initList();
    ListNode *current;
    int priority = 0;
    Process *process;

    for (int i = 0; (read = getline(&line, &len, file)) != -1; i++)
    {
        // vars
        if (i < 4)
        {
            int val = atoi(line);

            switch (i)
            {
            case 0:
                clk = val;
                break;
            case 1:
                stacks = val;
                break;
            case 2:
                queueL = val;
                break;
            default:
                newRamSz = val;
                break;
            }
        }

        // partsSize
        if (4 < i && i < 4 + stacks + 1)
        {
            int *val = (int *)malloc(sizeof(int));
            *val = atoi(line);
            addListNode1(partsizes, val);
        }

        // queuesLength

        if (i == 4 + stacks + 1 + 1)
        {
            tokens = str_split(line, ' ');
            if (tokens)
            {

                for (int j = 0; *(tokens + j); j++)
                {
                    int *val = (int *)malloc(sizeof(int));
                    int *val2 = (int *)malloc(sizeof(int));
                    *val = atoi(*(tokens + j));
                    *val2 = atoi(*(tokens + j));

                    addListNode1(queueLens, val);
                    addListNode1(queueLens2, val2);
                }
                free(tokens);
            }
        }

        // processes
        if (4 + stacks + 1 + 1 + 1 < i)
        {
            if (i == 4 + stacks + 1 + 1 + 1 + 1)
            {
                current = queueLens2->head;
            }

            if (!*((int *)current->val))
            {
                current = current->next;
                priority++;
                i++;
            }
            else
            {
                *((int *)current->val) -= 1;

                tokens = str_split(line, ' ');
                if (tokens)
                {
                    process = initProcess();
                    process->priority = stacks - priority;
                    for (int j = 0; *(tokens + j); j++)
                    {
                        int val = atoi(*(tokens + j));
                        switch (j)
                        {
                        case 0: // size
                            process->size = val;
                            break;
                        case 1: // clk
                            process->clocks = val;
                            process->exeTime = val * clk;
                            process->exeTime = (float)(process->exeTime) / 1000;
                            break;
                        case 2: // r
                            process->color.r = val;
                            break;
                        case 3: // g
                            process->color.g = val;
                            break;

                        case 4: // b
                            process->color.b = val;
                            break;

                        default: // a
                            process->color.a = val;
                            break;
                        }
                    }
                    free(tokens);
                    addListNode1(processes, process);
                }
            }
        }
    }

    fclose(file);
    if (line)
    {
        free(line);
    }

    return 1;
}

int checkUserData()
{
    // check initial vars
    int vars[4] = {clk, stacks, queueL, newRamSz};
    for (int i = 0; i < 4; i++)
    {
        if (!vars[i])
        {
            return 0;
        }
    }

    int comp[3] = {CLK, iStackLength, iQueueLength};
    for (int i = 0; i < 3; i++)
    {
        if (vars[i] != comp[i])
        {
            return 0;
        }
    }

    // check partsSize

    int totalPartsSz = 0;
    ListNode *current = partsizes->head;
    int val;
    while (current)
    {
        val = *(int *)(current->val);
        if (!val)
        {
            return 0;
        }
        totalPartsSz += val;

        current = current->next;
    }

    if (totalPartsSz != newRamSz)
    {
        return 0;
    }

    // check the queueLens
    int processesNum = 0;
    current = queueLens->head;
    while (current)
    {
        if (*((int *)current->val) > queueL)
        {
            return 0;
        }
        processesNum += *((int *)current->val);
        current = current->next;
    }

    // check the processes
    current = processes->head;
    Process *currentPrc;
    int clrs[4];
    while (current)
    {
        currentPrc = current->val;

        // clock check
        if (!currentPrc->clocks)
        {
            return 0;
        }

        // check priority
        if (currentPrc->priority <= 0 || currentPrc->priority > stacks)
        {
            return 0;
        }

        // colors check
        clrs[0] = currentPrc->color.r;
        clrs[1] = currentPrc->color.g;
        clrs[2] = currentPrc->color.b;
        clrs[3] = currentPrc->color.a;

        for (int i = 0; i < 4; i++)
        {
            if (!clrs[i])
            {
                return 0;
            }
        }

        current = current->next;
    }

    return 1;
}

int setUserData(Stack *iStk, Ram *ram)
{
    // free queueLens
    while (getListLength(queueLens))
    {
        removeListNode(queueLens, 0);
    }
    free(queueLens);

    // load processes
    ListNode *currentProcess = processes->head;

    Queue *currentQueue = popStackNode(iStack);
    Stack *tmpStack = initStack();
    pushStackNode(tmpStack, currentQueue);

    int currentPriority = iStackLength;

    while (currentProcess)
    {
        if (((Process *)currentProcess->val)->priority != currentPriority)
        {
            currentPriority -= 1;
            currentQueue = popStackNode(iStack);
            pushStackNode(tmpStack, currentQueue);
        }

        // load
        pushQueueNode(currentQueue, currentProcess->val);

        currentProcess = currentProcess->next;
        removeListNode(processes, 0);
    }

    while (!emptyStack(tmpStack))
    {
        pushStackNode(iStk, popStackNode(tmpStack));
    }
    free(tmpStack);

    free(processes);

    // setup ram
    ramSize = newRamSz;
    ListNode *current = ram->partitions->head;
    Partition *currentP;

    ListNode *currentPsz = partsizes->head;
    // delete partitions excess
    while (getListLength(ram->partitions) != getListLength(partsizes))
    {
        freeArray(((Partition *)getListQueue(ram->partitions)->val)->startAdr);
        removeListNode(ram->partitions, getListLength(ram->partitions) - 1);
    }

    while (current)
    {
        currentP = current->val;
        currentP->size = *((int *)currentPsz->val);

        current = current->next;
        currentPsz = currentPsz->next;
        removeListNode(partsizes, 0);
    }
    free(partsizes);
}
void eventFunc(SDL_Event e)
{
    // keyboard events
    if (e.type == SDL_KEYDOWN)
    {

        switch (e.key.keysym.sym)
        {

        case SDLK_q: // q
            runProcessor = !runProcessor;
            break;
        case SDLK_w: // w
            runQueue = !runQueue;
            break;
        case SDLK_e: // e first
            loadingStrategy = 0;
            break;
        case SDLK_r: // r best
            loadingStrategy = 1;
            break;
        case SDLK_t: // t worst
            loadingStrategy = 2;
            break;
        case SDLK_y: // y
            priority = !priority;
            break;
        case SDLK_u:
            printIndx += 1;
            if (printIndx > 2)
            {
                printIndx = 0;
            }
            break;
        case SDLK_i: // i
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
            while (stackLength(iStack))
            {
                currentQueue = popStackNode(iStack);
                pushStackNode(tmpStack, currentQueue);

                // get an empty queue
                if (queueLength(currentQueue) < iQueueLength)
                {
                    currentProcess = initProcess();
                    currentProcess->priority = iStackLength - currentNodeIndx; // invert
                    pushQueueNode(currentQueue, currentProcess);

                    break;
                }
                currentNodeIndx += 1;
            }

            // refiil everything
            while (!emptyStack(tmpStack))
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
            while (!emptyStack(iStack))
            {
                currentQueue = popStackNode(iStack);
                pushStackNode(tmpStack, currentQueue);

                if (queueLength(currentQueue))
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
            while (!emptyStack(tmpStack))
            {
                pushStackNode(iStack, popStackNode(tmpStack));
            }

            free(tmpStack);

            // merge after the new process takes an empty partition

            if (mergePartitions(ramPartitions)) // if merged
            {
                playSound(0, sound);
            };
        }

        if (printIndx == 1)
        {
            // print iStack
            printIStack(iStack);
        }
        if (printIndx == 2)
        {
            // print the ram
            printRam(ramPartitions);
        }

        // refresh
        SDL_SetRenderDrawColor(window->renderer, BGCLR.r, BGCLR.g, BGCLR.b, BGCLR.a);
        SDL_RenderClear(window->renderer);
        //

        // updateWIQueue(renderer, iQueueW, iQueue);
        // drawWIQueue(renderer, iQueueW);

        updateStatusW(renderer, statusW, runProcessor, runQueue, loadingStrategy, priority, sound, printIndx);
        drawStatusW(renderer, statusW);

        drawLegendW(renderer, legendW);

        updateRawW(renderer, ramW, ramPartitions);
        drawRawW(renderer, ramW);

        updateWIStack(renderer, iStackW, iStack);
        drawWIStack(renderer, iStackW);

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

    // getUserData
    if (getUserData())
    {
        printf("userdata loaded\n");
        if (checkUserData())
        {
            // setup the structs according to the userdata
            setUserData(iStack, ramPartitions);
            printf("userdata set\n");
        }
        else
        {
            printf("userdata corrupted\n");
        }
    }

    // widgets inits
    legendW = initLengendW(renderer);
    statusW = initStatusW(renderer);

    iStackW = initWIStack();
    ramW = initRamW();

    // init sound
    initSounds();

    mainLoop(window, eventFunc, loopFunc);

    return EXIT_SUCCESS;
}