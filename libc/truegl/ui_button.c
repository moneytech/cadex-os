/**
 * TrueGL Graphics Library v0.2
 * 
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
*/

#include <truegl/truegl.h>

/**
 * Draws a UI button at the specified x and y */
int draw_button(int x, int y, int w, int h, char *label)
{
    if(w > 0){
        drawRect(x, y, w, 15);
        print(x + 5, y + 2, label); 
    } else
    {
        drawRect(x, y, strlen(label) * 2, 15);
        print(x + 5, y + 2, label);
    } 
}
