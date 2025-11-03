#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <sys/wait.h>   
#include <string.h>     
#include <stdio.h>      

static void wputs(const char *s) {
    (void)write(STDOUT_FILENO, s, (unsigned)strlen(s));
}

int main(int argc, const char* argv[]) {
    // expect exactly two arguments: word and filename
    if (argc != 3) {
        wputs("ERROR: No arguments\n");
        return 1;
    }

    const char *word = argv[1];
    const char *file = argv[2];

    pid_t pid = fork();
    if (pid < 0) {
        // fork failed
        wputs("ERROR: fork failed\n");
        return 2;
    }

    if (pid == 0) {
        // child: exec grep -s -q <word> <file>
        char *eargs[] = {
            "grep",
            "-s",
            "-q",
            (char*)word,
            (char*)file,
            NULL
        };
        int rc = execv("/usr/bin/grep", eargs);
        if (rc == -1) {
            perror("exec");
            _exit(127);  
        }
        _exit(0);
    }

    // parents: wait for child and interpret grep's exit status
    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        wputs("ERROR: wait failed\n");
        return 2;
    }

    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        if (code == 0) {
            wputs("FOUND: ");
            wputs(word);
            wputs("\n");
            return 0;
        } else if (code == 1) {
            wputs("NOT FOUND: ");
            wputs(word);
            wputs("\n");
            return 0; 
        } else {
            // grep error 
            wputs("ERROR: ");
            wputs(file);
            wputs(" doesn't exist\n");
            return 2;
        }
    } else {
        wputs("ERROR: child did not exit normally\n");
        return 2;
    }
}
