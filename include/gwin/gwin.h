#ifndef GWIN_H
#define GWIN_H
#include <library/types.h>
#include <library/stdbool.h>
#define GWIN_VER 0.1.3
#define GWIN_VER_STR "0.1.3"
#define GWIN_WIN_SERVER "AceGUI"

typedef struct gwin_widget
{
    string name_s;
    string label;
    string public_name;
    int max_buff;
    int min_buff;
    int curr_buff;
    int width;
    int height;
    int x;
    int y;
    int z_index;
    int max_width;
    int min_width;
    int border_thick;
};

typedef enum
{
    GWIN_STDWINDOW,
    GWIN_STDWIN_HEADER,
    GWIN_STDWIN_TITLE,
    GWIN_STDWIN_DEFINE,
    GWIN_STDWIN_ANIM,
    GWIN_STDWIN_BUFF,
    GWIN_STDWIN,
} gwin_stdwin;
typedef union
{
    int server_status;
} gwin_server;
typedef union
{
    int serv_pid;
    string serv_name;
    string serv_hax_addr_str;
    int serv_hax_addr;
    bool isServerAvailable;
    bool isServerRunning;
    gwin_stdwin activeWindow;
    int port;
    int address;
    bool disable3dAcceleration;
} gwin_server_t;

#endif // !GWIN_H
