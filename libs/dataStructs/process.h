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

//generate a random int between minx and max
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


//free the process
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