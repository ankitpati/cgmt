/* dda.c */
/* Date  : 27 July 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

#define DELAY_MS    20

int main()
{
    int gd = DETECT, gm;
    int max_x, max_y, x1, y1, x2, y2, dx, dy, steps, i;
    double x, y, x_inc, y_inc;

    puts("x1?");
    scanf(" %d%*c", &x1);

    puts("y1?");
    scanf(" %d%*c", &y1);

    puts("x2?");
    scanf(" %d%*c", &x2);

    puts("y2?");
    scanf(" %d%*c", &y2);

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    cleardevice();

    setcolor(BLACK);

    max_x = getmaxx();
    max_y = getmaxy();

    if (x1 > max_x || x2 > max_x || y1 > max_y || y2 > max_y) {
        fprintf(stderr, "Point(s) given lie outside drawing area!\n");
        closegraph();
        exit(1);
    }

    x = x1;
    y = y1;

    dx = x2 - x1;
    dy = y2 - y1;

    steps = abs(abs(dx) > abs(dy) ? dx : dy);

    x_inc = dx / (double) steps;
    y_inc = dy / (double) steps;

    for (i = 0; i < steps; ++i) {
        x += x_inc;
        y += y_inc;

        putpixel(x, y, BLACK);
        delay(DELAY_MS);
    }

    getch();
    closegraph();
    return 0;
}
/* end of dda.c */
