/*
GWin Graphics/Window Server

Most of the functions and features are stubbed, ie. they don't work. They compile successfully but they don;'t do anything.
*/
#include <gwin/gwin.h>

#define GWIN_LIB
// #define ENABLE_EXP_FEAT
gwin_stdwin mainWindow;
gwin_server_t mainServ;

bool checkIfServerIsAvailable(){
    if(!mainServ.isServerRunning && !mainServ.isServerAvailable){
        mainServ.isServerAvailable = true;
        mainServ.isServerRunning = false;
        return mainServ.isServerAvailable;
    }
}
int return_current_active_server(){
    if(mainServ.isServerRunning){
        
    }
}
void resetSettings(){
    return;
}
void initServer(gwin_server_t gserv1){
    if(gserv1.isServerAvailable && gserv1.isServerRunning){
        gserv1.serv_hax_addr = 0x0BB13;
        gserv1.activeWindow = mainWindow;
    }
}