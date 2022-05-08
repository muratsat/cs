#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
 
int main(){
    int fd_src = open("source", O_RDONLY);
    int fd_dst = open("cracked", O_WRONLY | O_CREAT, 00666);


    unsigned long long BUFF_SIZE  = lseek(fd_src, 0, SEEK_END);
    lseek(fd_src, 0, SEEK_SET);

    char* byte = malloc(BUFF_SIZE);
    read(fd_src, byte, BUFF_SIZE);

    for(int i = 1; i < BUFF_SIZE;i++){
        if(byte[i-1] == 0x75 && byte[i] == 0x11){
            byte[i-1] = 0x74;
            break;
        }
    }

    write(fd_dst, byte, BUFF_SIZE);

    close(fd_src);
    close(fd_dst);
    return 0;
}