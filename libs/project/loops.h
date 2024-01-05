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
int currentNodeIndx;
Stack *tmpStack;
Queue *currentQueue;

Process *currentProcess;

int counter = CLK / REFRESHRATE;

void loopFunc(Window *window)
{
    if (counter >= CLK / REFRESHRATE)
    {

        // add processes to iQueue
        if (runQueue)
        {
            tmpStack = initStack();
            currentNodeIndx = 0;
            while (iStack->length)
            {
                currentQueue = popStackNode(iStack);
                pushStackNode(tmpStack, currentQueue);

                // get an empty queue
                if (currentQueue->length < iQueueLength)
                {
                    currentProcess = initProcess();
                    currentProcess->priority = currentNodeIndx;
                    pushQueueNode(currentQueue, currentProcess);

                    break;
                }
                currentNodeIndx += 1;
            }

            // refiil everything
            while (tmpStack->length)
            {
                pushStackNode(iStack, popStackNode(tmpStack));
            }

            free(tmpStack);
        }

        // processor

        if (runProcessor)
        {
            tickRam(ramPartitions);

            tmpStack = initStack();
            while (iStack->length)
            {
                currentQueue = popStackNode(iStack);
                pushStackNode(tmpStack, currentQueue);

                if (currentQueue->length)
                {
                    currentProcess = (Process *)popQueueNode(currentQueue);
                    if (!loadProcess(ramPartitions, currentProcess, loadingStrategy))
                    {
                        pushQueueNode(currentQueue, currentProcess);
                    }

                    if (priority)
                    {
                        break;
                    }
                }
            }
            // refill everything
            while (tmpStack->length)
            {
                pushStackNode(iStack, popStackNode(tmpStack));
            }

            free(tmpStack);

            // merge after the new process takes an empty partition

            mergePartitions(ramPartitions);
        }

        // print the ram
        // printRam(ramPartitions);

        // refresh
        SDL_SetRenderDrawColor(window->renderer, BGCLR.r, BGCLR.g, BGCLR.b, BGCLR.a);
        SDL_RenderClear(window->renderer);
        //

        // updateWIQueue(renderer, iQueueW, iQueue);
        // drawWIQueue(renderer, iQueueW);

        updateWIStack(renderer, iStackW, iStack);
        drawWIStack(renderer, iStackW);

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