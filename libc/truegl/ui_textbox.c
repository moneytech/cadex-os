/**
 * TrueGL Graphics Library v0.2
 *
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
*/

#include <truegl/truegl.h>

void create_edittext(int x, int y, int w, int h, char* placeholder, char* line)
{
    movable_scanf(x + 1, y + 1, &line, sizeof(line));
    drawRect(x, y, w + 2, h + 2);
}

