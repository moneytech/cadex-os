/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#ifndef _ASCII_H
#define _ASCII_H

#define ASCII_NUL       0
#define ASCII_SOH       1
#define ASCII_STX       2
#define ASCII_ETX       3
#define ASCII_EOT       4
#define ASCII_ENQ       5
#define ASCII_ACK       6
#define ASCII_BEL       7
#define ASCII_BS        8
#define ASCII_HT        9
#define ASCII_LF        10
#define ASCII_VT        11
#define ASCII_FF        12
#define ASCII_CR        13
#define ASCII_SO        14
#define ASCII_SI        15
#define ASCII_DLE       16
#define ASCII_DC1       17
#define ASCII_DC2       18
#define ASCII_DC3       19
#define ASCII_DC4       20
#define ASCII_NAK       21
#define ASCII_SYN       22
#define ASCII_ETB       23
#define ASCII_CAN       24
#define ASCII_EM        25
#define ASCII_SUB       26
#define ASCII_ESC       27
#define ASCII_FS        28
#define ASCII_GS        29
#define ASCII_RS        30
#define ASCII_US        31
#define ASCII_SP        32
#define ASCII_BANG      33
#define ASCII_DQUOTE    34
#define ASCII_HASH      35
#define ASCII_DOLLAR    36
#define ASCII_PERCENT   37
#define ASCII_AND       38
#define ASCII_SQUOTE    39
#define ASCII_LPAREN    40
#define ASCII_RPAREN    41
#define ASCII_STAR      42
#define ASCII_PLUS      43
#define ASCII_COMMA     44
#define ASCII_MINUS     45
#define ASCII_DOT       46
#define ASCII_SLASH     47
#define ASCII_0         48
#define ASCII_1         49
#define ASCII_2         50
#define ASCII_3         51
#define ASCII_4         52
#define ASCII_5         53
#define ASCII_6         54
#define ASCII_7         55
#define ASCII_8         56
#define ASCII_9         57
#define ASCII_COLON     58
#define ASCII_SEMICOLON 59
#define ASCII_LARROW    60
#define ASCII_EQUALS    61
#define ASCII_RARROW    62
#define ASCII_QUESTION  63
#define ASCII_AT        64
#define ASCII_A         65
#define ASCII_B         66
#define ASCII_C         67
#define ASCII_D         68
#define ASCII_E         69
#define ASCII_F         70
#define ASCII_G         71
#define ASCII_H         72
#define ASCII_I         73
#define ASCII_J         74
#define ASCII_K         75
#define ASCII_L         76
#define ASCII_M         77
#define ASCII_N         78
#define ASCII_O         79
#define ASCII_P         80
#define ASCII_Q         81
#define ASCII_R         82
#define ASCII_S         83
#define ASCII_T         84
#define ASCII_U         85
#define ASCII_V         86
#define ASCII_W         87
#define ASCII_X         88
#define ASCII_Y         89
#define ASCII_Z         90
#define ASCII_LBRACKET  91
#define ASCII_BACKSLASH 92
#define ASCII_RBRACKET  93
#define ASCII_CARET     94
#define ASCII__         95
#define ASCII_BACKTICK  96
#define ASCII_a         97
#define ASCII_b         98
#define ASCII_c         99
#define ASCII_d         100
#define ASCII_e         101
#define ASCII_f         102
#define ASCII_g         103
#define ASCII_h         104
#define ASCII_i         105
#define ASCII_j         106
#define ASCII_k         107
#define ASCII_l         108
#define ASCII_m         109
#define ASCII_n         110
#define ASCII_o         111
#define ASCII_p         112
#define ASCII_q         113
#define ASCII_r         114
#define ASCII_s         115
#define ASCII_t         116
#define ASCII_u         117
#define ASCII_v         118
#define ASCII_w         119
#define ASCII_x         120
#define ASCII_y         121
#define ASCII_z         122
#define ASCII_LBRACE    123
#define ASCII_PIPE      124
#define ASCII_RBRACE    125
#define ASCII_TILDE     126
#define ASCII_DEL       127

/*
The following are not 7-bit ASCII values,
but abstract keycodes for commonly used keys,
which we put in the upper half of a character
value returned by the keyboard driver.
*/

#define KEY_INSERT    128
#define KEY_DELETE    129
#define KEY_HOME      130
#define KEY_END       131
#define KEY_PAGE_UP   132
#define KEY_PAGE_DOWN 133
#define KEY_UP        134
#define KEY_DOWN      135
#define KEY_LEFT      136
#define KEY_RIGHT     137
#define KEY_HELP      138

#define KEY_F1  140
#define KEY_F2  141
#define KEY_F3  142
#define KEY_F4  143
#define KEY_F5  144
#define KEY_F6  145
#define KEY_F7  146
#define KEY_F8  147
#define KEY_F9  148
#define KEY_F10 149
#define KEY_F11 150
#define KEY_F12 151
#define KEY_F13 152
#define KEY_F14 153
#define KEY_F15 154

#define KEY_INVALID 255

#endif
