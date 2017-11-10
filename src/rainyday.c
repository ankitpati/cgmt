/* rainyday.c */
/* Date  : 10 November 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

int main()
{
    int gd = DETECT, gm;
    int max_x, max_y, i;

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    max_x = getmaxx();
    max_y = getmaxy();

    line(20, 380, 580, 380);

    line(25, 380, 35, 340);
    line(45, 380, 35, 340);
    line(35, 310, 25, 330);

    delay(20);

    circle(35, 300, 10);

    line(35, 340, 35, 310);
    line(35, 310, 50, 330);
    line(50, 330, 50, 280);
    line(15, 280, 85, 280);

    arc(50, 280, 0, 180, 35);
    arc(55, 330, 180, 360, 5);

    for (i = 0; i < 100; ++i)
        outtextxy(random(max_x), random(max_y - 50), "|");

    getch();
    closegraph();
    return 0;
}
/* end of rainyday.c */
