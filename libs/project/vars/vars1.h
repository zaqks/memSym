const int CLK = 1000; // ms

Window *window;
SDL_Renderer *renderer;

Queue *iQueue; // instruction queue
Ram *ramPartitions; // ram

WidgetIQueue *iQueueW;
WidgetLegend *legendW;
WidgetRam *ramW;

bool runProcessor = true;
bool runQueue = false;
