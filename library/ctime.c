/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/
#include <time.h>
#include <sys/time.h>

char * ctime(const time_t * timep) {
    return asctime(localtime(timep));
}
