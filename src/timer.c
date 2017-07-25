/* timer.c */
/* Date  : 23 July 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

#define DELAY_MS    50
#define MAX_COUNT   (1000 / (DELAY_MS) - 1)
#define MAX_SEC     59
#define MAX_MINUTE  59
#define MAX_HOUR    11

int main()
{
    int gd = DETECT, gm;
    int centre_x, centre_y, radius, count, second, minute, hour,
        second_length, minute_length, hour_length;
    double angle;

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    cleardevice();

    centre_x = getmaxx() / 2;
    centre_y = getmaxy() / 2;

    radius = centre_x < centre_y ? centre_x : centre_y;

    second_length = radius * 9 / 10;
    minute_length = radius * 7 / 10;
    hour_length   = radius * 5 / 10;

    setcolor(BLACK);
    circle(centre_x, centre_y, radius);

    for (
        /* initialisation */
        count = second = minute = hour = 0;

        /* test */
        !kbhit();

        /* increment */
        count  == MAX_COUNT  ? count  = 0, second++ : count++,
        second == MAX_SEC    ? second = 0, minute++ :       0,
        minute == MAX_MINUTE ? minute = 0, hour++   :       0,
        hour   == MAX_HOUR   ? hour   = 0           :       0
    ) {
        delay(DELAY_MS);
        if (count) continue;

        cleardevice();

        setcolor(BLACK);
        circle(centre_x, centre_y, radius);

        angle = second * M_PI / 30 - M_PI / 2;

        setcolor(RED);
        line(
            centre_x, centre_y, centre_x + second_length * cos(angle),
            centre_y + second_length * sin(angle)
        );

        angle = minute * M_PI / 30 - M_PI / 2;

        setcolor(GREEN);
        line(
            centre_x, centre_y, centre_x + minute_length * cos(angle),
            centre_y + minute_length * sin(angle)
        );

        angle = hour * M_PI / 30 - M_PI / 2;

        setcolor(BLUE);
        line(
            centre_x, centre_y, centre_x + hour_length * cos(angle),
            centre_y + hour_length * sin(angle)
        );
    }

    getch();
    closegraph();
    return 0;
}
/* end of timer.c */
