#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>   
#include <stdio.h>    
#include <stdlib.h>   

int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        // no arguments provided
        write(STDOUT_FILENO, "ERROR: no arguments\n", 20);
        return 1;
    }

    // number of user provided args 
    int num_args = argc - 1;
    int mid = num_args / 2;

    char* eargs[5];  
    eargs[0] = "echo";

    if (num_args % 2 == 1) {
        // odd count means one middle argument
        eargs[1] = (char*)argv[mid + 1];
        eargs[2] = NULL;
    } else {
        // even count means two middle arguments
        eargs[1] = (char*)argv[mid];
        eargs[2] = (char*)argv[mid + 1];
        eargs[3] = NULL;
    }

    // echo with chosen arguments
    int ret = execv("/bin/echo", eargs);
    if (ret == -1) {
        perror("exec");
        return 1;
    }

    return 0;
}
