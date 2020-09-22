/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/
/**
 * An application to clear the screen
*/
#include <library/stdio.h>
#include <library/color.h>

int main(int argc, char *argv[])
{
    // Just print out '\f' and boom! The screen is cleared!
    printf("\f");
    return 0;
}