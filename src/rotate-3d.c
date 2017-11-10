#include <graphics.h>

#define RAD(X) ( ((X) * M_PI) / 180.0 )

int max_x, max_y, mid_x, mid_y;

void axis()
{
    line(mid_x, 0, mid_x, max_y);
    line(0, mid_y, max_x, mid_y);
}

int main()
{
    int o, x1, x2, y1, y2;
    int gd = DETECT, gm;
    double sin_o, cos_o;

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    max_x = getmaxx();
    max_y = getmaxy();

    mid_x = max_x / 2;
    mid_y = max_y / 2;

    axis();

    bar3d(mid_x + 50, mid_y - 100, mid_x + 60, mid_y - 90, 5, 1);

    puts("Rotating Angle?");
    scanf(" %d%*c", &o);
    o = RAD(o);

    sin_o = sin(o);
    cos_o = cos(o);

    x1 = 50 * cos_o - 100 * sin_o;
    y1 = 50 * sin_o + 100 * cos_o;
    x2 = 60 * cos_o -  90 * sin_o;
    y2 = 60 * sin_o +  90 * cos_o;

    axis();
    puts("Rotation about z-axis...");
    bar3d(mid_x + x1, mid_y - y1, mid_x + x2, mid_y - y2, 5, 1);

    puts("Press enter to continue.\n");
    getchar();
    cleardevice();

    axis();
    puts("Rotation about x-axis...");
    bar3d(mid_x + 50, mid_y - x1, mid_x + 60, mid_y - x2, 5, 1);

    puts("Press enter to continue.\n");
    getchar();
    cleardevice();

    axis();
    puts("Rotation about y-axis...");
    bar3d(mid_x + x1, mid_y - 100, mid_x + x2, mid_y - 90, 5, 1);

    delay(1000);
    getch();
    closegraph();
    return 0;
}
