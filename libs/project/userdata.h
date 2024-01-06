#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <SDL2/SDL.h>

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
int ram;
int stacks;
int queueL;

int partsizes[] = {};

int queueLens[] = {};

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
#define MaxProcCLK 20
int lastProcessId = 0;
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
    process->exeTime = (float)((process->clocks) * clk) / 1000; // in s

    // set the size
    process->size = randomNum(1, 6) * sizeof(Process);

    // set the priority
    process->priority = randomNum(0, stacks);

    // set a color
    process->color.r = randomNum(0, 255);
    process->color.g = randomNum(0, 255);
    process->color.b = randomNum(0, 255);
    process->color.a = 255;

    return process;
}

Process *processes[] = {};

int main()
{

    FILE *file;
    char *line = NULL;
    size_t len = 0;
    __ssize_t read;

    file = fopen("files/data", "r");
    if (!file)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; (read = getline(&line, &len, file)) != -1; i++)
    {
        // first 4 lines
        switch (i)
        {
        case 0: // clk
            clk = atoi(line);
            break;
        case 1: // ram
            ram = atoi(line);
            break;
        case 2: // stacks
            stacks = atoi(line);
            break;
        case 3: // queue len
            queueL = atoi(line);
            break;

        default:
            // part sizes
            if (i < 4 + stacks)
            {
                partsizes[i - 4] = atoi(line);
            }
            // queue sizes
            if (i == 4 + stacks + 2)
            {
                char **tokens = str_split(line, ' '); // ' ' not " "

                for (int i = 0; *(tokens + i); i++)
                {
                    queueLens[i] = atoi(*(tokens + i));
                    free(*(tokens + i));
                }
                free(tokens);
            }

            // processes
            if (i > 4 + stacks + 2 + 1)
            {
                for (int j = 0; j < stacks; j++)
                {
                    if (queueLens[j])
                    {
                        Process *process = initProcess();
                        process->priority = j;
                        char **tokens = str_split(line, ' ');
                        int val;
                        for (int k = 0; *(tokens + k); k++)
                        {
                            val = atoi(*(tokens + k));
                            switch (k)
                            {
                            case 0:
                                process->size = val;
                                break;
                            case 1:
                                process->clocks = val;
                                break;
                            case 2:
                                process->color.r = val;
                                break;
                            case 3:
                                process->color.g = val;
                                break;
                            case 4:
                                process->color.b = val;
                                break;
                            case 5:
                                process->color.a = val;
                                break;
                            default:
                                break;
                            }

                            free(*(tokens + k));
                        }

                        processes[i - (4 + stacks + 2 + 1 + 1)] = process;
                        queueLens[j]--;

                        free(tokens);

                        break;
                    }
                }
            }
            break;
        }
    }

    fclose(file);
    if (line)
    {
        free(line);
    }

    return EXIT_SUCCESS;
}

// clk
// ram
// stakcs
// queue length

// partsizes

// size clk r g b a