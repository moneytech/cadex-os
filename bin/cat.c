#include <stdio.h>

#define TAG_BUFFER_SIZE 256
int ctemp;
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        syscall_chdir(argv[0]);
        //printf("got root\n");
        // int dir_fd = syscall_open_file("/", 0, 0);
        // syscall_object_set_tag(dir_fd, "ROOT");
        //printf("Opened root directory\n");
        int fd = syscall_open_file(argv[1], 0, 0);
        char buffer[1000];
        int n;
        //printf("reading file...\n");
        while ((n = syscall_object_read(fd, buffer, 100)) > 0)
        {
            buffer[n] = 0;
            printf("%s", buffer);
            flush();
        }
        n = syscall_object_read(fd, buffer, 100);
        buffer[n] = 0;
        syscall_object_close(fd);
        printf("\n");
        _process_exit(0);
    } else
    {
        printf("usage: cat [parent-dir] [filename]\n");
        return 0;
    }
    
    

    return 0;
}
