const int CLK = 1000; // ms

Window *window;
SDL_Renderer *renderer;
Queue *iQueue; // instruction queue

WidgetIQueue *iQueueW;
WidgetLegend *legendW;


bool runProcessor = true;
bool runQueue = false;


