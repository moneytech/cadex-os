#include "library/syscalls.h"
#include "library/user-io.h"
#include "library/string.h"
#include "library/color.h"

int main(int argc, char *argv[]){
    int dims[2];
    syscall_object_size(KNO_STDWIN, dims, 2);

	int width = dims[0];
	int height = dims[1];
    renderWindow(KNO_STDWIN);
    // clearScreen(0, 0, width, height);
    setTextColor(BLUE);
    flush();
    return 0;
}