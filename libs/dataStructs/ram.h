#define ramSize  1024*1024; // 1024Kb

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

    //create the partitions

    Partition *partition = initPartition(10);

    return ram;
}