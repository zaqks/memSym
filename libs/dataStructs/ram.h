const int ramSize = 1024 * 1024; // 1024Kb

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
    // first fit
    ListNode *current = ram->partitions->head;
    Partition *crntPart;
    while (current)
    {
        crntPart = (Partition *)current->val;
        if (!crntPart->occupied)
        {
            if (crntPart->size >= process->size)
            {
                pushArrayNode(crntPart->startAdr, process);
                crntPart->occupied = true;

                return 1;
            }
        }
        current = current->next;
    }

    return 0;
}

void tickRam(Ram *ram)
{
    ListNode *current = ram->partitions->head;
    while (current)
    {
        current = current->next;
    }

    printf("tick ram\n");
}