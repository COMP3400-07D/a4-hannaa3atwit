#include <stdio.h>
#include <ctype.h>

int main(int argc, const char *argv[]) {
    // if no arguments provided, print error and return 1
    if (argc <= 1) {
        printf("ERROR: No arguments\n");
        return 1;
    }

    // loop through each argument
    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];
        // print each character in uppercase
        for (int j = 0; arg[j] != '\0'; j++) {
            putchar(toupper((unsigned char)arg[j]));
        }
        // print comma if not the last argument
        if (i < argc - 1) {
            putchar(',');
        }
    }

    putchar('\n');
    return 0;
}
