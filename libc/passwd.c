/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include <passwd.h>

struct passwd *p;

extern void endpwent() { /* Nothing here. */ }
extern int getpwuid(int a) {
    p->pw_name = "root";
    return a;
}
extern int getprocuid() { return 10; }
