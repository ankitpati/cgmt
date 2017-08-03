/* tangledcircs.c */
/* Date  : 03 August 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

int main()
{
    int gd = DETECT, gm;
    int centre_x, centre_y, radius;
    size_t i;
    double angle;

    initgraph(&gd, &gm, "");

    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    centre_x = getmaxx() / 2;
    centre_y = getmaxy() / 2;

    radius = (centre_x < centre_y ? centre_x : centre_y) / 3;

    circle(centre_x, centre_y, radius);

    for (i = 0; i < 6; ++i){
        angle = i * M_PI / 3 - M_PI / 2;
        circle(
            centre_x + radius * cos(angle),
            centre_y + radius * sin(angle),
            radius
        );
    }

    getch();
    closegraph();
    return 0;
}
/* end of tangledcircs.c */
