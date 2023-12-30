//#include "Text.h"

typedef struct
{
    int v;
    int h;

} Padding;

typedef struct
{
    Padding padding;

    Text *text;
    SDL_Rect *body;

} Button;

Button *createButton(SDL_Renderer *renderer, TTF_Font *font, char *fontPath, int fontSize, char *text, SDL_Color fgClr, SDL_Color bgClr, int x, int y, Padding padding)
{
    Button *btn = (Button *)malloc(sizeof(Button));
    btn->text = createText(renderer, font, fontPath, fontSize, text, fgClr, x + padding.h, y + padding.v);

    btn->body = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    btn->body->x = x;
    btn->body->y = y;
    btn->body->w = btn->text->rect->w + padding.h * 2;
    btn->body->h = btn->text->rect->h + padding.v * 2;

    btn->padding = padding;

    return btn;
}

void drawButton(SDL_Renderer *renderer, Button *btn)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, btn->body);
    drawText(renderer, btn->text);
}

void btnClickFunc(SDL_Event e, Button *btn, void (*func)())
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point mouse;
        mouse.x = e.motion.x;
        mouse.y = e.motion.y;

        if (SDL_PointInRect(&mouse, btn->body))
        {
            func();
        };
    }
}