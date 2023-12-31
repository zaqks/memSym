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
    for (int i = 0; i < 3; i++)
    {
        partition = initPartition(ramSize / 3);
        addListNode1(ram->partitions, partition);
    }

    return ram;
}