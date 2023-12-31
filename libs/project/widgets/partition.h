typedef struct
{
    SDL_Rect *mainRect;
} WidgetPartition;

WidgetPartition *initPartitionW(Partition *partition, int w, int h, int x, int y)
{
    WidgetPartition *widget = (WidgetPartition *)malloc(sizeof(WidgetPartition));

    return widget;
}

void drawPartitionW(SDL_Renderer *renderer, WidgetPartition *widget) {}

void erasePartitionW(WidgetPartition *widget) {}
