/* cornercircs.c */
/* Date  : 21 July 2017
 * Author: Ankit Pati
 */

#include <graphics.h>

int main()
{
    int gd = DETECT, gm;
    int max_x, max_y;

    initgraph(&gd, &gm, "");

    max_x = getmaxx();
    max_y = getmaxy();

    line   (0, 0, 100, 100);
    circle (100, 100, 100);

    line   (max_x - 100, max_y - 100, max_x, max_y);
    circle (max_x - 100, max_y - 100, 100);

    line   (100, max_y - 100, 0, max_y);
    circle (100, max_y - 100, 100);

    line   (max_x - 100, 100, max_x, 0);
    circle (max_x - 100, 100, 100);

    getch();
    closegraph();
    return 0;
}
/* end of cornercircs.c */
