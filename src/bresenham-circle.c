/* bresenham-circle.c */
/* Date  : 04 August 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

#define DELAY_MS    20

int main()
{
    int gd = DETECT, gm;

    int max_x, max_y, r, x, y, cx, cy, d;

    puts("Radius?");
    scanf(" %d%*c", &r);

    puts("Centre: x?");
    scanf(" %d%*c", &cx);

    puts("Centre: y?");
    scanf(" %d%*c", &cy);

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    max_x = getmaxx();
    max_y = getmaxy();

    if (cx > max_x || cy > max_y) {
        fprintf(stderr, "Centre lies outside drawing area!\n");
        closegraph();
        exit(1);
    }

    d = 3 - 2*r;

    for (x = 0, y = r; x <= y; ++x) {
        putpixel(cx - x, cx - y, 1);
        setcolor(1);
        line(cx, cy, cx - x, cx - y);

        putpixel(cx - x, cx + y, 2);
        setcolor(2);
        line(cx, cy, cx - x, cx + y);

        putpixel(cx + x, cx - y, 3);
        setcolor(3);
        line(cx, cy, cx + x, cx - y);

        putpixel(cx + x, cx + y, 4);
        setcolor(4);
        line(cx, cy, cx + x, cx + y);

        putpixel(cx - y, cx - x, 5);
        setcolor(5);
        line(cx, cy, cx - y, cx - x);

        putpixel(cx - y, cx + x, 6);
        setcolor(6);
        line(cx, cy, cx - y, cx + x);

        putpixel(cx + y, cx - x, 7);
        setcolor(7);
        line(cx, cy, cx + y, cx - x);

        putpixel(cx + y, cx + x, 8);
        setcolor(8);
        line(cx, cy, cx + y, cx + x);

        if (d < 0)
            d += 4*x + 6;
        else {
            --y;
            d += 4*(x - y) + 10;
        }

        delay(DELAY_MS);
    }

    getch();
    closegraph();
    return 0;
}
/* end of bresenham-circle.c */
