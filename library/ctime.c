/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/
#include <library/types.h>

char * ctime(const time_t * timep) {
    return asctime(localtime(timep));
}
