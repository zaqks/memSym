typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
} Parallelogram;

Parallelogram *initParallelogram(int x1,
                                 int y1,
                                 int x2,
                                 int y2,
                                 int x3,
                                 int y3)
{
    Parallelogram *shape = (Parallelogram *)malloc(sizeof(Parallelogram));

    shape->x3 = x3;
    shape->y3 = y3;

    shape->x1 = x1;
    shape->y1 = y1;
    shape->x2 = x2;
    shape->y2 = y2;

    return shape;
}

void drawParallelogram(SDL_Renderer *renderer, Parallelogram *shape, bool fill)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if (fill)
    {
    }
    else
    {

        int lines[4][4] =
            {
                {shape->x1, shape->y1, shape->x2 - shape->x3, shape->y1 + shape->y3}, // 1
                {shape->x2 - shape->x3, shape->y1 + shape->y3, shape->x2, shape->y2}, // 2
                {shape->x1 + shape->x3, shape->y2 - shape->y3, shape->x2, shape->y2}, // 3
                {shape->x1, shape->y1, shape->x1 + shape->x3, shape->y2 - shape->y3}, // 4
            };

        for (int i = 0; i < 4; i++)
        {
            SDL_RenderDrawLine(renderer, lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
        }
    }
}
