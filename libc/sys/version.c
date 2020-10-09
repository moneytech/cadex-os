/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License.
 * See the file LICENSE for details.
*/

/**
 * version.c: Contains versioning info and functions returning version info about Cadex OS
 * 
 * This file is a part of the Standard Cadex Library
*/

#include <stdclib.h>

// Return _LTS_REL constant defined in 'library/version.h'
char *get_system_version(){
    // Return _LTS_REL_
    return _LTS_REL_;
}