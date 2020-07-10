#include <library/stdio.h>
#include <library/color.h>

int main(int argc, char *argv[]){
    clearScreen(0, 0, getWindowDimens("width"), getWindowDimens("height"));
    return 0;
}