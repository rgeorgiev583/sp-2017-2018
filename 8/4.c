#include <unistd.h>

int main(int argc, char** argv)
{
    int fds1[2];
    pipe(fds1);

    if (fork())
    {
        dup2(fds1[1], 1);
        close(fds1[0]);
        close(fds1[1]);
        argv[2] = argv[1];
        argv[0] = "head";
        argv[1] = "-n";
        execvp("head", argv);
    }
    else
    {
        dup2(fds1[0], 0);
        close(fds1[0]);
        close(fds1[1]);

        int fds2[2];
        pipe(fds2);

        if (fork())
        {
            dup2(fds2[1], 1);
            close(fds2[0]);
            close(fds2[1]);
            execlp("grep", "grep", argv[2], NULL);
        }
        else
        {
            close(fds1[0]);
            dup2(fds2[0], 0);
            close(fds2[0]);
            close(fds2[1]);
            execlp("wc", "wc", "-l", NULL);
        }
    }

    return 0;
}
