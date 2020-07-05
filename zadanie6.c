#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();

    if (pid > 0)
    {
        // Rodzic (parent)
        int status;
        wait(&status);
    }

    if (pid == 0)
    {
        // Dziecko (child)
        char *path = "/bin/ls";
        execl(path, "ls", NULL);
        printf("CHILDES FINISHED \n");
        _exit(0);
    }

    if (pid < 0)
    {
        printf("ERROR PID");
        _exit(1);
    }

    return 0;
}
