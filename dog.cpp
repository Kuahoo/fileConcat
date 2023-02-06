#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "dog.h"

#define BUFFER_SIZE 32768

int fileOpener(char *fileToOpen){
    //taken from coding guidelines and standards. Daniel Bittman, Darrell Long, Ethan Miller
    int fileDescriptor;
    if((fileDescriptor = open(fileToOpen, O_RDWR)) == -1){fprintf(stderr, "dog: %s: %s\n", fileToOpen, strerror(errno));}
    return fileDescriptor;
}

int fileReader(int fileToRead, char *buffer[]){
    return read(fileToRead, buffer, sizeof(*buffer)/sizeof(buffer[0]));
}

int fileWriter(char *buffer[]){ 
    int val;
    if(( val = (write(1, buffer, sizeof(*buffer)/sizeof(buffer[0])))) == -1){fprintf(stderr, "\ndog: write error: %s\n", strerror(errno)); exit(1);}
    return val; 
}

int fileCloser(int fileToClose){
    return close(fileToClose);
}

//reads in from filedescriptor and outputs based on buffer
void toStdout(int fileDescriptor, char *buffer[]){
    while(fileReader(fileDescriptor, buffer) > 0) {
        fileWriter(buffer);
    }
}

int main(int argc, char *argv[]){ 
    int currCount = 1;
    char *buffer[BUFFER_SIZE];
    //check if program is ran by itself, if so duplicate stdin
    if(argc == 1){
        toStdout(0, buffer);
    }else{
        while(currCount != argc){
            //check if '-' is part of the arguments entered. If so duplicate stdin
            if(*argv[currCount] == '-'){
                toStdout(0, buffer);
            }else{
                //open regular file and write it out to stdout
                int fd = fileOpener(argv[currCount]);
                toStdout(fd, buffer);
                fileCloser(fd);
            }
            ++currCount;
        }
    }
    return 0;
}

