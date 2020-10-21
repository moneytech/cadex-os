/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * libbmf: BitMapFont reader
 * @author HyperCreeck
 */

#include <libbmf/bmf.h>

bmf_font_t load_bmf(char *font_name) {
    if (!strcmp(font_name, "pearl")) {

    } else if (!strcmp(font_name, "")) {

    } else {
        dbg_printf("load_bmf(): Invalid font %s\n", font_name);
        return;
    }
}
