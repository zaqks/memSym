Window *window;
SDL_Renderer *renderer;

//Queue *iQueue;      // instruction queue
Stack *iStack;      // iQueue Stack
Ram *ramPartitions; // ram

//WidgetIQueue *iQueueW;

WidgetRam *ramW;

WidgetStatus *statusW;

bool runProcessor = false;
bool runQueue = false;

/*
first f
best f
worst f
*/
int loadingStrategy = 0;
int priority = false;