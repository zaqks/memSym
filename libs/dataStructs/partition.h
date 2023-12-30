typedef struct partition
{
    struct partition *startAdr;
    int size;
    bool occupied;
} Partition;