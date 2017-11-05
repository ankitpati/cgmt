/* polygon-clipping.c */
/* Date  : 06 October 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

#define DELAY_MS 1000

typedef enum {
    X, Y, Z,
} axis;

typedef enum {  /* tbrl */
    LEFT   = 1, /* 0001 */
    RIGHT  = 2, /* 0010 */
    BOTTOM = 4, /* 0100 */
    TOP    = 8, /* 1000 */
} outcodes;

typedef enum {
    BOTH_INSIDE   = 0, /* 00 */
    FIRST_INSIDE  = 1, /* 01 */
    FIRST_OUTSIDE = 2, /* 10 */
    BOTH_OUTSIDE  = 3, /* 11 */
} conditions;

void my_drawpoly(int **poly, int sides)
{
    int i, *p, *q;
    char ps[40];

    for (i = 1; i <= sides; ++i) {
        p = poly[i - 1];
        q = poly[i != sides ? i : 0];

        sprintf(ps, "(%d, %d)", p[X], p[Y]);
        outtextxy(p[X], p[Y], ps);

        line(p[X], p[Y], q[X], q[Y]);

        sprintf(ps, "(%d, %d)", q[X], q[Y]);
        outtextxy(q[X], q[Y], ps);
    }
}

void freepoly(int **poly, int sides)
{
    int i;
    for (i = 0; i < sides; ++i) free(poly[i]);
    free(poly);
}

unsigned isout(int xy, int boundary, outcodes oc)
{
    return oc == LEFT || oc == TOP ? xy < boundary : xy > boundary;
}

int **clip(int ***poly, int *sides, int boundary, outcodes oc)
{
#define ADD_POINT(X_COOR, Y_COOR) do { \
    clipped = realloc(clipped, ++cn * sizeof(*clipped)); \
    clipped[cn - 1] = malloc(2 * sizeof(**clipped)); \
    clipped[cn - 1][X] = (X_COOR); \
    clipped[cn - 1][Y] = (Y_COOR); \
} while (0)

    int **clipped, cn, *p, *q, i;
    double x1, y1, x2, y2, x, y, m, c;
    conditions cond;
    axis a;

    clipped = NULL;
    cn = 0;

    a = (oc == LEFT || oc == RIGHT ? X : Y);

    for (i = 1; i <= *sides; ++i) {
        p = (*poly)[i - 1];
        q = (*poly)[i != *sides ? i : 0];

        x1 = p[X];
        y1 = p[Y];

        x2 = q[X];
        y2 = q[Y];

        cond = isout(p[a], boundary, oc) << 1 | isout(q[a], boundary, oc);

        switch (cond) {
        case BOTH_INSIDE:
            /* add second point */
            ADD_POINT(q[X], q[Y]);
            break;

        case BOTH_OUTSIDE:
            /* add no points */
            break;

        case FIRST_INSIDE:
        case FIRST_OUTSIDE:
            /* add intersection */
            m = (y1 - y2) / (x1 - x2);
            c = ((y1 - m*x1) + (y2 - m*x2)) / 2.0; /* for accuracy */

            x = y = 0;

            switch (oc) {
            case LEFT:
            case RIGHT:
                x = boundary;
                y = m * x + c;
                break;

            case TOP:
            case BOTTOM:
                y = boundary;
                x = (y - c) / m;
                break;
            }

            ADD_POINT(x, y);

            if (cond == FIRST_INSIDE)
                break;

            /* add second point */
            ADD_POINT(q[X], q[Y]);

            break;
        }
    }

    freepoly(*poly, *sides);

    *sides = cn;
    *poly = clipped;
    return clipped;

#undef ADD_POINT
}

int main()
{
#define DELAY_AND_DRAW() do { \
    delay(DELAY_MS); \
    cleardevice(); \
    rectangle(left, top, right, bottom); \
    my_drawpoly(poly, n); \
} while (0)

    int gd = DETECT, gm;
    int max_x, max_y, left, top, right, bottom, **poly, temp, n, i;
    char **p, acc[80];

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

    puts("Number of Points?");
    scanf(" %d%*c", &n);

    p = malloc(n * sizeof(*p));

    poly = malloc(n * sizeof(*poly));
    for (i = 0; i < n; ++i) poly[i] = malloc(2 * sizeof(**poly));

    puts("Vertex Co-ordinates?");
    for (i = 0; i < n; ++i) {
        scanf(" %d %d%*c", &poly[i][X], &poly[i][Y]);

        if (
            poly[i][X] < 0 || poly[i][X] > max_x ||
            poly[i][Y] < 0 || poly[i][Y] > max_y
        ) {
            fprintf(stderr, "Outside drawing area! Try again.\n");
            --i;
            continue;
        }

        p[i] = malloc(40);
        sprintf(p[i], "(%d, %d)", poly[i][X], poly[i][Y]);

        outtextxy(poly[i][X], poly[i][Y], p[i]);

        if (!i) continue; /* skip the first point */

        line(poly[i - 1][X], poly[i - 1][Y], poly[i][X], poly[i][Y]);
    }
    line(poly[n - 1][X], poly[n - 1][Y], poly[0][X], poly[0][Y]);

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

    clip(&poly, &n, left, LEFT);
    DELAY_AND_DRAW();

    clip(&poly, &n, top, TOP);
    DELAY_AND_DRAW();

    clip(&poly, &n, right, RIGHT);
    DELAY_AND_DRAW();

    clip(&poly, &n, bottom, BOTTOM);
    DELAY_AND_DRAW();

    getch();
    closegraph();
    return 0;
}
/* end of polygon-clipping.c */
