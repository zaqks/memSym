const int CLK = 1000; // ms

Window *window;
SDL_Renderer *renderer;

Queue *iQueue; // instruction queue
Ram *ramPartitions; // ram

WidgetIQueue *iQueueW;
WidgetRam *ramW;

bool runProcessor = false;
bool runQueue = false;

/*
first f
best f
worst f
*/
int loadingStrategy = 0;