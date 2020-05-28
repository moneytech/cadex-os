#include "exception.h"

#define EXEC_ERR 190
#define ENOTFOUND 400
#define ENOTACC 409
#define ENOEXEC 199

void handleException(int excode){
    switch(excode){
        case 1:
            printf("FATAL: Exception occured while execution. Details: \njava.lang.NullPointerException, Tried to access an object at null pointer reference\r\n    at java.util.Core\r\n   at java.lang.Corona");

        default:
            printf("Exception");
    }
}