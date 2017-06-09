#include <stdio.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("usage: %s command\n", argv[0]);
        printf("  Most likely you either did not pass a command,\n"
               "  or did not enclose it in quotes so that it does\n"
               "  not get read as multiple arguments.\n");
        return 1;
    }


    printf("Would execute command %s\n", argv[1]);
    return 0;
}
