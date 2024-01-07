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
int ram;
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
                ram = val;
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
    int vars[4] = {clk, stacks, queueL, ram};
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

    if (totalPartsSz != ram)
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

int setUserData()
{

    // init ram
    ramSize = ram;

    // load processes
}