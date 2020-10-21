/*
Copyright (C) 2019-2020 The CadexOS Project
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef KSHELL_H
#define KSHELL_H

typedef struct {
    char *device_name;
    char *user_login_name;
    char *current_directory;
    char *custom_kshell_command;
    int last_run_proc_exitcode;
    int kshell_prompt_index;
    int last_process_run;
} kshell_t;

int kshell_launch();
void kshell_show_login_prompt();

#endif
