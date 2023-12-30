void eventFunc(SDL_Event e) {}

int counter = 0;
void loopFunc(Window *window)
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