#include <assert.h>

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

    file = fopen("../../data/userdata", "r");
    if (!file)
    {
        return 0;
    }

    partsizes = initList();
    queueLens = initList();
    processes = initList();

    char **tokens;

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
                ram = val;
                break;
            case 2:
                stacks = val;
                break;
            default:
                queueL = val;
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
                    *val = atoi(*(tokens + j));
                    addListNode1(queueLens, val);
                }
                free(tokens);
            }
        }

        // processes
        if (4 + stacks + 1 + 1 + 1 < i)
        {
            if (i == 4 + stacks + 1 + 1 + 1 + 1)
            {
                current = queueLens->head;
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
                        switch (j)
                        {
                        case 0: // size
                            break;
                        case 1: // clk
                            break;
                        case 2: // r
                            break;
                        case 3: // g
                            break;
                        case 4: // b
                            break;

                        default: // a
                            break;
                        }

                        printf("%d\n", atoi(*(tokens + j)));
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
    int vars[4] = {clk, ram, stacks, queueL};
    for (int i = 0; i < 4; i++)
    {
        if (!vars[i])
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

    // dont check the queueLens

    return 1;
}

int setUserData() {}