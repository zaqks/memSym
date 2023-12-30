typedef struct
{
    int id;
    char *arvTime;
    int clocks;
    int exeTime;
} Process;

int randomNum(int min, int max)
{
    srand(time(NULL)); // set the seed
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

    // set the clocks + exeTime
    process->clocks = randomNum(10, 100);
    process->exeTime = (process->clocks) / 1000; // in seconds

    return process;
}

void pushProcessQueue(Queue *queue, Process *process) {
    pushQueueNode(queue, process);
}