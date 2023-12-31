int lastProcessId = 0;

typedef struct
{
    int id;
    char *arvTime;
    int clocks;
    int exeTime;
    int size;

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
    process->clocks = randomNum(10, 100);
    process->exeTime = (process->clocks) / 1000; // in seconds

    // set the size
    process->size = randomNum(1, 6) * sizeof(Process);

    //set a color
    process->color.r = randomNum(0, 255);
    process->color.g = randomNum(0, 255);
    process->color.b = randomNum(0, 255);
    process->color.a = 255;


    return process;
}

void pushProcessQueue(Queue *queue, Process *process)
{
    pushQueueNode(queue, process);
    printf("new process created\n");
}