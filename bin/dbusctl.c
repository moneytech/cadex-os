/**
 * DBus serice control system: Controls how dbus pipe should work
*/
#include <stdio.h>
#include <library/scanf.h>
#include <shared/dbus_data.h>

int main(int argc, const char *argv[])
{
    if(argc <= 0){
        return 0;
    } else {
        struct dbus_data *d;
        d->prog_exec = "/bin/dbusctl.exe";
        d->dbus_is_init = true;
        return 0;
    }
    return 0;
}