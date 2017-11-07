/* rotate.c */
/* Date  : 21 August 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

#define X   0
#define Y   1
#define H   2

#define RAD(X) ( ((X) * M_PI) / 180.0 )

double **matrix_mul(double **m1, int r1, int c1, double m2[][3], int r2, int c2)
{
    int i, j, k;
    double **t;

    if (c1 != r2) return NULL;

    t = malloc(r1 * sizeof(*t));
    for (i = 0; i < r1; ++i) t[i] = malloc(c2 * sizeof(**t));

    for (i = 0; i < r1; ++i)
        for (j = 0; j < c2; ++j)
            for (k = t[i][j] = 0; k < r2; ++k)
                t[i][j] += m1[i][k] * m2[k][j];

    return t;
}

void drawhomopoly(double **poly, int n)
{
    int i;
    char p[40];
    double *q, *r;

    for (i = 1; i <= n; ++i) {
        q = poly[i - 1];
        r = poly[i != n ? i : 0];

        line(q[X], q[Y], r[X], r[Y]);

        sprintf(p, "(%.0lf, %.0lf)", q[X], q[Y]);
        outtextxy(q[X], q[Y], p);
    }
}

int main()
{
    int gd = DETECT, gm;
    int max_x, max_y, arb_x, arb_y, colour, choice, n, i;
    double **poly, **to_free, **tmpmat1, **tmpmat2, angle, sin_a, cos_a;
    char **p, acc[80];

    double tmat[][3] = {
        { 1.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 9.0, 9.0, 1.0 }
    }; /* replace 9.0 with Tx and Ty once available */

    double rmat[][3] = {
        { 9.0, 9.0, 0.0 },
        { 9.0, 9.0, 0.0 },
        { 0.0, 0.0, 1.0 }
    }; /* replace 9.0 with appropriate values once computed */

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
        scanf(" %lf %lf%*c", &poly[i][X], &poly[i][Y]);

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
        sprintf(p[i], "(%.0lf, %.0lf)", poly[i][X], poly[i][Y]);

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
        "1. Rotate Clockwise about Origin\n"
        "2. Rotate Counter-Clockwise about Origin\n"
        "3. Rotate Clockwise about Arbitrary Point\n"
        "4. Rotate Counter-Clockwise about Arbitrary Point\n"
    );

    do {
        printf("?> "); fflush(stdout);
        scanf(" %d%*c", &choice);

        switch (choice) {
        case 0:
            break;

        case 1:
        case 2:
            puts("Angle?");
            scanf(" %lf%*c", &angle);
            angle = RAD(angle);

            sin_a = sin(angle);
            cos_a = cos(angle);

            rmat[0][0] = rmat[1][1] = cos_a;
            rmat[0][1] = rmat[1][0] = sin_a;
            if (choice == 2) rmat[0][1] *= -1;
            else             rmat[1][0] *= -1;

            setcolor(colour = colour == 14 ? 0 : colour + 1);
            drawhomopoly(to_free = matrix_mul(poly, n, 3, rmat, 3, 3), n);

            for (i = 0; i < n; ++i) free(to_free[i]);
            free(to_free);

            break;

        case 3:
        case 4:
            puts("Angle?");
            scanf(" %lf%*c", &angle);
            angle = RAD(angle);

            sin_a = sin(angle);
            cos_a = cos(angle);

            puts("Arbitrary Point?");
            scanf(" %d %d%*c", &arb_x, &arb_y);

            tmat[2][0] = -arb_x;
            tmat[2][1] = -arb_y;

            tmpmat1 = matrix_mul(poly, n, 3, tmat, 3, 3);

            rmat[0][0] = rmat[1][1] = cos_a;
            rmat[0][1] = rmat[1][0] = sin_a;
            if (choice == 4) rmat[0][1] *= -1;
            else             rmat[1][0] *= -1;

            tmpmat2 = matrix_mul(tmpmat1, n, 3, rmat, 3, 3);
            for (i = 0; i < n; ++i) free(tmpmat1[i]);
            free(tmpmat1);

            tmat[2][0] = arb_x;
            tmat[2][1] = arb_y;

            to_free = matrix_mul(tmpmat2, n, 3, tmat, 3, 3);
            for (i = 0; i < n; ++i) free(tmpmat2[i]);
            free(tmpmat2);

            setcolor(colour = colour == 14 ? 0 : colour + 1);
            drawhomopoly(to_free, n);
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
/* end of rotate.c */
