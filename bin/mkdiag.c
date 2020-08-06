/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

/* An application to make graphical dialogs */
#include <library/stdio.h>
#include <library/color.h>

int main(int argc, char const *argv[])
{
    // Check if length of command-line arguments is lesser than 0
    if(argc < 0){
        // If length of command-line arguments is lesser than 0
        printf("MKDiag version 0.2\nUsage: mkdiag.exe [OPTION]... (title|bgcolor|fgcolor|button)\n\nThis program is a part of Cadex OSUtils v0.11");
    }
    return 0;
}
