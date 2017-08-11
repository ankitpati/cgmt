/* floodfill.c */
/* Date  : 11 August 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

void my_floodfill(int x, int y)
{
    if (getpixel(x, y) != WHITE) return;

    putpixel(x, y, LIGHTGRAY);

    my_floodfill(x - 1, y);
    my_floodfill(x, y - 1);
    my_floodfill(x + 1, y);
    my_floodfill(x, y + 1);
}

int main()
{
    int gd = DETECT, gm;
    int max_x, max_y, *x, *y, seed_x, seed_y, n, i;
    char **p, seed[40], acc[80];

    puts("Number of Points?");
    scanf(" %d%*c", &n);

    x = malloc(n * sizeof(*x));
    y = malloc(n * sizeof(*y));
    p = malloc(n * sizeof(*p));

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    cleardevice();

    setcolor(BLACK);

    max_x = getmaxx();
    max_y = getmaxy();

    puts("Vertex Co-ordinates?");
    for (i = 0; i < n; ++i) {
        scanf(" %d %d%*c", x + i, y + i);

        if (x[i] < 0 || y[i] < 0 || x[i] > max_x || y[i] > max_y) {
            fprintf(stderr, "Outside drawing area! Try again.\n");
            --i;
            continue;
        }

        p[i] = malloc(40);
        sprintf(p[i], "(%d, %d)", x[i], y[i]);

        outtextxy(x[i], y[i], p[i]);

        if (!i) continue; /* skip the first point */

        line(x[i - 1], y[i - 1], x[i], y[i]);
    }
    line(x[n - 1], y[n - 1], *x, *y);

    puts("Co-ordinates of Seed Point?");
    scanf(" %d %d%*c", &seed_x, &seed_y);
    sprintf(seed, "(%d, %d)", seed_x, seed_y);
    putpixel(seed_x, seed_y, RED);
    outtextxy(seed_x, seed_y, seed);

    puts("Is the displayed polygon and seed point accurate? (Y/n)");
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

    cleardevice();

    for (i = 0; i < n - 1; ++i) line(x[i], y[i], x[i + 1], y[i + 1]);
    line(x[n - 1], y[n - 1], *x, *y);

    my_floodfill(seed_x, seed_y);

    delay(1000);
    getch();
    closegraph();
    return 0;
}
/* end of floodfill.c */
