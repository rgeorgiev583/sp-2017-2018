#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 1000
#define MAXARGS 100


int main(int argc, char** argv)
{
    while (1)
    {
        write(1, "$ ", 2);
        char cmd[BUFSIZE];
        size_t cmd_len = read(0, cmd, BUFSIZE);
        cmd[cmd_len - 1] = '\0';

        char* cmd_argv[MAXARGS];
        cmd_argv[0] = strtok(cmd, " ");
        size_t i = 0;
        do
        {
            i++;
            cmd_argv[i] = strtok(NULL, " ");
        }
        while (cmd_argv[i]);

        if (!strcmp(cmd_argv[0], "exit") || !strcmp(cmd_argv[0], "quit"))
            exit(0);

        if (!fork() && !execvp(cmd_argv[0], cmd_argv))
        {
            printf("error: command `%s` does not exist\n", cmd_argv[0]);
            exit(1);
        }
        else
        {
            int status;
            wait(&status);
        }
    }

    return 0;
}
