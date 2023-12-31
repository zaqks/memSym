int lastProcessId = 0;

typedef struct
{
    int id;
    char *arvTime;
    int clocks;
    int exeTime;
    int size;
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

    return process;
}

void pushProcessQueue(Queue *queue, Process *process)
{
    pushQueueNode(queue, process);
    printf("new process added\n");
}