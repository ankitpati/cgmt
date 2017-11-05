#include <graphics.h>

int main()
{
    int gd = DETECT, gm;
    int x1, y1, x2, y2, max_y, i, j, k, m, n, p;
    double b[4][8], F, phi;

    int a[4][8] = {
        { 100, 200, 200, 100, 100, 200, 200, 100 },
        { 100, 100, 200, 200, 100, 100, 200, 200 },
        { 100, 100, 100, 100, 200, 200, 200, 200 },
    };

    double par[4][4] = {
        { 1, 0, 9, 0 },
        { 0, 1, 9, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 1 },
    };

    puts("Values of F and phi?"); /* Sane Example: F = 0.5, phi = 30 */
    scanf(" %lf %lf%*c", &F, &phi);

    phi *= M_PI / 180.0; /* degrees to radians */

    par[0][2] = F * cos(phi);
    par[1][2] = F * sin(phi);

    m = 4;
    n = 4;
    p = 8;

    for (i = 0; i < m; ++i)
        for (k = 0; k < p; ++k)
            b[i][k] = 0;

    for (i = 0; i < m; ++i)
        for (k = 0; k < p; ++k)
            for (j = 0; j < n; ++j)
                b[i][k] += par[i][j] * a[j][k];

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    max_y = getmaxy();

    /* front plane display */
    for (j = 0; j < 3; ++j) {
        x1 = b[0][j];
        y1 = b[1][j];

        x2 = b[0][j + 1];
        y2 = b[1][j + 1];

        line(x1, max_y - y1, x2, max_y - y2);
    }

    x1 = b[0][3];
    y1 = b[1][3];

    x2 = b[0][0];
    y2 = b[1][0];

    line(x1, max_y - y1, x2, max_y - y2);

    /* back plane display */
    setcolor(GREEN);

    for (j = 4; j < 7; ++j) {
        x1 = b[0][j];
        y1 = b[1][j];

        x2 = b[0][j + 1];
        y2 = b[1][j + 1];

        line(x1, max_y - y1, x2, max_y - y2);
    }

    x1 = b[0][7];
    y1 = b[1][7];

    x2 = b[0][4];
    y2 = b[1][4];

    line(x1, max_y - y1, x2, max_y - y2);

    setcolor(4);

    for (i = 0; i < 4; ++i) {
        x1 = b[0][i];
        y1 = b[1][i];

        x2 = b[0][4 + i];
        y2 = b[1][4 + i];

        line(x1, max_y - y1, x2, max_y - y2);
    }

    getch();
    closegraph();
    return 0;
}
