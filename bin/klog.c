/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * Kernel logger utility
 */

#include <stdio.h>

void warn(char *s) {
  renderWindow(WN_STDWINDOW);
  setTextColor(198, 0, 198, 0);
  printf("%s", s);
  resetColor();
}
void crit(char *s) {
  renderWindow(WN_STDWINDOW);
  setTextColor(CLEAR_RED, 0);
  printf("%s", s);
  resetColor();
}
void err(char *s) {
  renderWindow(WN_STDWINDOW);
  setTextColor(CLEAR_RED, 0);
  printf("%s", s);
  resetColor();
}
void info(char *s) {
  renderWindow(WN_STDWINDOW);
  setTextColor(BLUE, 0);
  printf("%s", s);
  resetColor();
}
int main(int argc, char *argv[]) {
  if (argc > 2) {
    if (!strcmp(argv[0], "-warn")) {
      warn(argv[1]);
    } else if (!strcmp(argv[0], "-info")) {
      info(argv[1]);
    } else if (!strcmp(argv[0], "-err")) {
      err(argv[1]);
    } else if (!strcmp(argv[0], "-crit")) {
      crit(argv[1]);
    } else {
      syscall_debug("[KLog] Initialized\n");
    }
  }
  return 0;
}
