/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#ifndef SUL_BASE64_H
#define SUL_BASE64_H

/**
 * Encode an ASCII string to base64
 * @param input_str Input string
 * @param len_str Length of input string
 * @returns char*
 */
char *base64_encode(char input_str[], int len_str);

#endif //  SUL_BASE64_H
