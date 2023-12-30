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

int counter = 0;
void loopFunc(Window *window)
{
    if (runProcessor)
    {
        if (counter >= CLK / REFRESHRATE)
        {
            SDL_SetRenderDrawColor(window->renderer, BGCLR.r, BGCLR.g, BGCLR.b, BGCLR.a);
            SDL_RenderClear(window->renderer);
            //
            drawLegendW(renderer, legendW);

            updateWIQueue(renderer, iQueueW, iQueue);
            drawWIQueue(renderer, iQueueW);

            //
            SDL_RenderPresent(window->renderer);
            counter = 0;
        }

        counter++;
    }
}