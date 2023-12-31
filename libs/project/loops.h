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
        case 101: // e
            break;
        case 114: // r
            break;
        case 116: // t
            break;
        case 121: // y
            break;
        default:
            break;
        }
    }
}

int counter = CLK / REFRESHRATE;
void loopFunc(Window *window)
{
    if (runProcessor)
    {
        if (counter >= CLK / REFRESHRATE)
        {
            // add processes
            if (runQueue)
            {
                

                if (iQueue->length < iQueueLength)
                {
                    pushProcessQueue(iQueue, initProcess());
                }
                
            }

            // refresh
            SDL_SetRenderDrawColor(window->renderer, BGCLR.r, BGCLR.g, BGCLR.b, BGCLR.a);
            SDL_RenderClear(window->renderer);
            //

            updateWIQueue(renderer, iQueueW, iQueue);
            drawWIQueue(renderer, iQueueW);

            updateRawW(renderer, ramW);
            drawRawW(renderer, ramW);

            drawLegendW(renderer, legendW);
            //
            SDL_RenderPresent(window->renderer);
            counter = 0;
        }

        counter++;
    }
}