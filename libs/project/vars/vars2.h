Window *window;
SDL_Renderer *renderer;

// Queue *iQueue;      // instruction queue
Stack *iStack;      // iQueue Stack
Ram *ramPartitions; // ram

// WidgetIQueue *iQueueW;

WidgetRam *ramW;

WidgetStatus *statusW;

bool runProcessor = false;
bool runQueue = false;

int loadingStrategy = 0; /*first f best f worst f*/
bool priority = false;
bool sound = true;