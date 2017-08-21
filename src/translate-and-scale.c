/* translate-and-scale.c */
/* Date  : 18 August 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

#define X   0
#define Y   1
#define H   2

int **matrix_mul(int **m1, int r1, int c1, int m2[][3], int r2, int c2)
{
    int i, j, k, **t;

    if (c1 != r2) return NULL;

    t = malloc(r1 * sizeof(*t));
    for (i = 0; i < r1; ++i) t[i] = malloc(c2 * sizeof(**t));

    for (i = 0; i < r1; ++i)
        for (j = 0; j < c2; ++j)
            for (k = t[i][j] = 0; k < r2; ++k)
                t[i][j] += m1[i][k] * m2[k][j];

    return t;
}

void drawhomopoly(int **poly, int n)
{
    int i;
    char p[40];

    for (i = 0; i < n - 1; ++i) {
        line(poly[i][X], poly[i][Y], poly[i + 1][X], poly[i + 1][Y]);

        sprintf(p, "(%d, %d)", poly[i][X], poly[i][Y]);
        outtextxy(poly[i][X], poly[i][Y], p);
    }

    line(poly[n - 1][X], poly[n - 1][Y], poly[0][X], poly[0][Y]);
}

int main()
{
    int gd = DETECT, gm;
    int max_x, max_y, **poly, **to_free, colour, choice, n, i;
    char **p, acc[80];

    int tmat[][3] = {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 9, 9, 1 }
    }; /* replace 9 with Tx and Ty once available */

    int smat[][3] = {
        { 9, 0, 0 },
        { 0, 9, 0 },
        { 0, 0, 1 }
    }; /* replace 9 with Sx and Sy once available */

    puts("Number of Points?");
    scanf(" %d%*c", &n);

    p = malloc(n * sizeof(*p));

    poly = malloc(n * sizeof(*poly));
    for (i = 0; i < n; ++i) poly[i] = malloc(3 * sizeof(**poly));

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    cleardevice();

    setcolor(colour = 0);

    max_x = getmaxx();
    max_y = getmaxy();

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

        poly[i][H] = 1; /* for homogenous matrix */

        p[i] = malloc(40);
        sprintf(p[i], "(%d, %d)", poly[i][X], poly[i][Y]);

        outtextxy(poly[i][X], poly[i][Y], p[i]);

        if (!i) continue; /* skip the first point */

        line(poly[i - 1][X], poly[i - 1][Y], poly[i][X], poly[i][Y]);
    }
    line(poly[n - 1][X], poly[n - 1][Y], poly[0][X], poly[0][Y]);

    puts("Is the displayed polygon accurate? (Y/n)");
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

    puts(
        "What would you like to do?\n"
        "0. Exit\n"
        "1. Translate\n"
        "2. Scale\n"
    );

    do {
        printf("?> "); fflush(stdout);
        scanf(" %d%*c", &choice);

        switch (choice) {
        case 0:
            break;

        case 1:
            puts("Translation in X Direction?");
            scanf(" %d%*c", &tmat[2][0]);

            puts("Translation in Y Direction?");
            scanf(" %d%*c", &tmat[2][1]);

            setcolor(colour = colour == 14 ? 0 : colour + 1);
            drawhomopoly(to_free = matrix_mul(poly, n, 3, tmat, 3, 3), n);

            for (i = 0; i < n; ++i) free(to_free[i]);
            free(to_free);

            break;

        case 2:
            puts("Scaling in X Direction?");
            scanf(" %d%*c", &smat[0][0]);

            puts("Scaling in Y Direction?");
            scanf(" %d%*c", &smat[1][1]);

            setcolor(colour = colour == 14 ? 0 : colour + 1);
            drawhomopoly(to_free = matrix_mul(poly, n, 3, smat, 3, 3), n);

            for (i = 0; i < n; ++i) free(to_free[i]);
            free(to_free);

            break;

        default:
            fprintf(stderr, "Incorrect Choice!\n");
            break;
        }

        putchar('\n');
    } while (choice);

    delay(1000);
    getch();
    closegraph();
    return 0;
}
/* end of translate-and-scale.c */
