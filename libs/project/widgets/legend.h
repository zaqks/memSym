#define LegendsNum 10
char *legends[LegendsNum] = {"<q> toggle processor",
                             "<w> toggle queue",
                             "<e> first fit",
                             "<r> best fit",
                             "<t> worst fit",
                             "<y> toggle priority",
                             "<u> toggle print mode",
                             "<i> toggle sound",
                             "",
                             "<Esc> exit"};

const int legendPadding = 10;
TTF_Font *legendFont;

typedef struct
{
    SDL_Rect *mainRect;
    Text *txt[LegendsNum];

} WidgetLegend;

WidgetLegend *initLengendW(SDL_Renderer *renderer)
{
    legendFont = TTF_OpenFont("assets/fonts/QuickSand.ttf", 15);
    WidgetLegend *legend = (WidgetLegend *)malloc(sizeof(WidgetLegend));

    // create text
    int previousY = 0;

    int mainRectW = 0;
    int mainRectH = 0;

    Text *txt;
    for (int i = 0; i < LegendsNum; i++)
    {
        txt = createText(renderer, legendFont, NULL, 0, legends[i], WHITECLR, 0, 0);

        legend->txt[i] = txt;
        txt->rect->y = previousY;
        previousY += txt->rect->h;
        // calc rect dims
        mainRectH += txt->rect->h;
        // get max width
        if (txt->rect->w > mainRectW)
        {
            mainRectW = txt->rect->w;
        }
    }

    // create rect
    SDL_Rect *mainRect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    mainRect->h = mainRectH + 2 * legendPadding;
    mainRect->w = mainRectW + 2 * legendPadding;
    mainRect->x = SCREEN_WIDTH - (mainRect->w + MAINPADDING);
    mainRect->y = SCREEN_HEIGHT - (mainRect->h + MAINPADDING);

    legend->mainRect = mainRect;

    // text postion
    for (int i = 0; i < LegendsNum; i++)
    {
        txt = legend->txt[i];
        txt->rect->x += mainRect->x + legendPadding;
        txt->rect->y += mainRect->y + legendPadding;
    }

    return legend;
}

void drawLegendW(SDL_Renderer *renderer, WidgetLegend *widget)
{

    // draw rect
    SDL_SetRenderDrawColor(renderer, WHITECLR.r, WHITECLR.g, WHITECLR.b, WHITECLR.a);
    SDL_RenderDrawRect(renderer, widget->mainRect);

    // draw text
    for (int i = 0; i < LegendsNum; i++)
    {
        drawText(renderer, widget->txt[i]);
    }
}