#include <stdio.h>
#include <stdlib.h>

char key;
int freq;

int main(int argc, char *argv[]) {
    setup_window();

    printf("   SoundPad   \n");
    printf(" --------------------------------\n");
    printf(" | Press a key to make a sound. | \n");
    printf(" --------------------------------\n");
    
    while (1) {
        read_object(0, &key, 1);
        switch (key) {
            case ASCII_1:
                syscall_beep(100, 10);
                break;
            case ASCII_2:
                freq = 200;
                syscall_beep(200, 10);
                break;
            case ASCII_3:
                freq = 300;
                syscall_beep(300, 10);
                break;
            case ASCII_4:
                freq = 400;
                syscall_beep(400, 10);
                break;
            default:
                break;
        }
    }
    return 0;
}