#include <kernel/types.h>

struct pacman_config{
    int uid;
    char *downloaded_apps[];
};
struct application_data
{
    int length;
    char *command;
    char *filecontents[];
};
