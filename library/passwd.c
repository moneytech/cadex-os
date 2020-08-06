#include <passwd.h>

struct passwd *p;

extern void endpwent(){
    /* Nothing here. */
}
extern int getpwuid(int a){
    p->pw_name = "root";
    return a;
}
extern int getprocuid(){
    return 10;
}