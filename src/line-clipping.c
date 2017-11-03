/* line-clipping.c */
/* Date  : 29 September 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

#define DELAY_MS 1000

typedef enum {  /* tbrl */
    LEFT   = 1, /* 0001 */
    RIGHT  = 2, /* 0010 */
    BOTTOM = 4, /* 0100 */
    TOP    = 8, /* 1000 */
} outcodes;

unsigned getoutcode(
    double x, double y, int left, int top, int right, int bottom
)
{
    unsigned outcode = 0;
    outcode |= x < left ? LEFT : x > right  ? RIGHT  : 0;
    outcode |= y < top  ? TOP  : y > bottom ? BOTTOM : 0;
    return outcode;
}

int main()
{
    int gd = DETECT, gm;
    int max_x, max_y, left, top, right, bottom, temp;
    double x1, y1, x2, y2, *x, *y, m, c;
    unsigned oc1, oc2, oc;
    char p[40], acc[80];

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    max_x = getmaxx();
    max_y = getmaxy();

    puts("Window Co-ordinates?");
    scanf(" %d %d %d %d%*c", &left, &top, &right, &bottom);

    if (left > right) {
        temp  = left;
        left  = right;
        right = temp;
    }

    if (top > bottom) {
        temp   = top;
        top    = bottom;
        bottom = temp;
    }

    if (left < 0 || right > max_x || top < 0 || bottom > max_y) {
        fprintf(stderr, "Outside drawing area! Re-run program to try again.\n");
        exit(1);
    }

    rectangle(left, top, right, bottom);

    for (;;) {
        puts("First End-Point?");
        scanf(" %lf %lf%*c", &x1, &y1);
        if (x1 < 0 || x1 > max_x || y1 < 0 || y1 > max_y) {
            fprintf(stderr, "Outside drawing area! Try again.\n");
            continue;
        }
        break;
    }
    sprintf(p, "(%d, %d)", (int) x1, (int) y1);
    outtextxy(x1, y1, p);

    for (;;) {
        puts("Second End-Point?");
        scanf(" %lf %lf%*c", &x2, &y2);
        if (x2 < 0 || x2 > max_x || y2 < 0 || y2 > max_y) {
            fprintf(stderr, "Outside drawing area! Try again.\n");
            continue;
        }
        break;
    }
    sprintf(p, "(%d, %d)", (int) x2, (int) y2);
    outtextxy(x2, y2, p);

    line(x1, y1, x2, y2);

    puts("Are the displayed window and line accurate? (Y/n)");
    fgets(acc, 80, stdin);

    switch (*acc) {
    case 'y':
    case 'Y':
    case '\n': /* intended fall-through */
        break;

    default:
        fprintf(stderr, "Re-run program and supply information again!\n");
        closegraph();
        exit(1);
        break;
    }

    m = (y1 - y2) / (x1 - x2);
    c = ((y1 - m*x1) + (y2 - m*x2)) / 2.0; /* for accuracy */

    for (;;) {
        delay(DELAY_MS);
        cleardevice();
        rectangle(left, top, right, bottom);

        oc1 = getoutcode(x1, y1, left, top, right, bottom);
        oc2 = getoutcode(x2, y2, left, top, right, bottom);

        /* trivial reject */
        if (oc1 & oc2)
            break;

        sprintf(p, "(%d, %d)", (int) x1, (int) y1);
        outtextxy(x1, y1, p);

        sprintf(p, "(%d, %d)", (int) x2, (int) y2);
        outtextxy(x2, y2, p);

        line(x1, y1, x2, y2);

        /* trivial accept */
        if (!(oc1 | oc2))
            break;

        if (oc1) {
            oc = oc1;
            x  = &x1;
            y  = &y1;
        }
        else {
            oc = oc2;
            x  = &x2;
            y  = &y2;
        }

        if (oc & LEFT) {
            *x = left;
            *y = m * *x + c;
            continue;
        }

        if (oc & RIGHT) {
            *x = right;
            *y = m * *x + c;
            continue;
        }

        if (oc & BOTTOM) {
            *y = bottom;
            *x = (*y - c) / m;
            continue;
        }

        if (oc & TOP) {
            *y = top;
            *x = (*y - c) / m;
            continue;
        }
    }

    getch();
    closegraph();
    return 0;
}
/* end of line-clipping.c */
