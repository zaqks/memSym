void eventFunc(SDL_Event e)
{
    // keyboard events
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {

        case 113: // q
            runProcessor = !runProcessor;
            break;
        case 119: // w
            runQueue = !runQueue;
            break;
        case 101: // e first
            loadingStrategy = 0;
            break;
        case 114: // r best
            loadingStrategy = 1;
            break;
        case 116: // t worst
            loadingStrategy = 2;
            break;
        case 121: // y
            priority = !priority;
            break;
        default:
            break;
        }
    }
}
Process *processLoad;

int counter = CLK / REFRESHRATE;
void loopFunc(Window *window)
{

    if (counter >= CLK / REFRESHRATE)
    {
        // add processes to iQueue
        if (runQueue)
        {

            if (iQueue->length < iQueueLength)
            {
                pushProcessQueue(iQueue, initProcess());
            }
        }

        // process
        if (runProcessor)
        {
            tickRam(ramPartitions);

            if (iQueue->length > 0)
            {

                processLoad = (Process *)popQueueNode(iQueue);
                if (!loadProcess(ramPartitions, processLoad, loadingStrategy))
                {
                    pushQueueNode(iQueue, processLoad);
                }
            }
        }

        // refresh
        SDL_SetRenderDrawColor(window->renderer, BGCLR.r, BGCLR.g, BGCLR.b, BGCLR.a);
        SDL_RenderClear(window->renderer);
        //

        updateWIQueue(renderer, iQueueW, iQueue);
        drawWIQueue(renderer, iQueueW);

        updateRawW(renderer, ramW, ramPartitions);
        drawRawW(renderer, ramW);

        updateStatusW(renderer, statusW, runProcessor, runQueue, loadingStrategy, priority);
        drawStatusW(renderer, statusW);

        drawLegendW(renderer, legendW);
        //
        SDL_RenderPresent(window->renderer);
        counter = 0;
    }

    counter++;
}