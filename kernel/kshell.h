/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef KSHELL_H
#define KSHELL_H

typedef struct
{
    char *device_name;
    int kshell_prompt_index;
    char *current_directory;
    char *custom_kshell_command;
    int last_run_proc_exitcode;
    int last_process_run;
} kshell_t;

int kshell_launch();

#endif
