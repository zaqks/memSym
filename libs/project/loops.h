void eventFunc(SDL_Event e)
{
    // keyboard events
    if (e.type == SDL_KEYDOWN)
    {

        switch (e.key.keysym.sym)
        {

        case SDLK_q: // q
            runProcessor = !runProcessor;
            break;
        case SDLK_w: // w
            runQueue = !runQueue;
            break;
        case SDLK_e: // e first
            loadingStrategy = 0;
            break;
        case SDLK_r: // r best
            loadingStrategy = 1;
            break;
        case SDLK_t: // t worst
            loadingStrategy = 2;
            break;
        case SDLK_y: // y
            priority = !priority;
            break;
        case SDLK_u:
            printIndx += 1;
            if (printIndx > 2)
            {
                printIndx = 0;
            }
            break;
        case SDLK_i: // i
            sound = !sound;
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
            while (stackLength(iStack))
            {
                currentQueue = popStackNode(iStack);
                pushStackNode(tmpStack, currentQueue);

                // get an empty queue
                if (queueLength(currentQueue) < iQueueLength)
                {
                    currentProcess = initProcess();
                    currentProcess->priority = iStackLength - currentNodeIndx; // invert
                    pushQueueNode(currentQueue, currentProcess);

                    break;
                }
                currentNodeIndx += 1;
            }

            // refiil everything
            while (!emptyStack(tmpStack))
            {
                pushStackNode(iStack, popStackNode(tmpStack));
            }

            free(tmpStack);
        }

        // processor

        if (runProcessor)
        {
            if (tickRam(ramPartitions)) // if a process if completed
            {
                playSound(3, sound);
            }
            else
            {
                playSound(1, sound); // if this is a normal tick
            }

            tmpStack = initStack();
            while (!emptyStack(iStack))
            {
                currentQueue = popStackNode(iStack);
                pushStackNode(tmpStack, currentQueue);

                if (queueLength(currentQueue))
                {
                    currentProcess = (Process *)popQueueNode(currentQueue);
                    // load process
                    if (!loadProcess(ramPartitions, currentProcess, loadingStrategy))
                    {
                        pushQueueNode(currentQueue, currentProcess);
                    }
                    else
                    {
                        playSound(2, sound); // start execution
                    }

                    if (priority)
                    {
                        break;
                    }
                }
            }
            // refill everything
            while (!emptyStack(tmpStack))
            {
                pushStackNode(iStack, popStackNode(tmpStack));
            }

            free(tmpStack);

            // merge after the new process takes an empty partition

            if (mergePartitions(ramPartitions)) // if merged
            {
                playSound(0, sound);
            };
        }

        if (printIndx == 1)
        {
            // print iStack
            printIStack(iStack);
        }
        if (printIndx == 2)
        {
            // print the ram
            printRam(ramPartitions);
        }

        // refresh
        SDL_SetRenderDrawColor(window->renderer, BGCLR.r, BGCLR.g, BGCLR.b, BGCLR.a);
        SDL_RenderClear(window->renderer);
        //

        // updateWIQueue(renderer, iQueueW, iQueue);
        // drawWIQueue(renderer, iQueueW);

        updateStatusW(renderer, statusW, runProcessor, runQueue, loadingStrategy, priority, sound, printIndx);
        drawStatusW(renderer, statusW);

        drawLegendW(renderer, legendW);

        updateRawW(renderer, ramW, ramPartitions);
        drawRawW(renderer, ramW);

        updateWIStack(renderer, iStackW, iStack);
        drawWIStack(renderer, iStackW);

        //
        SDL_RenderPresent(window->renderer);
        counter = 0;
    }

    counter++;
}