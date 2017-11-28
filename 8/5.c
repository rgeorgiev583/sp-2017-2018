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
        argv[0] = "grep";
        execvp("grep", argv);
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
            execlp("sort", "sort", NULL);
        }
        else
        {
            dup2(fds2[0], 0);
            close(fds2[0]);
            close(fds2[1]);

            int fds3[2];
            pipe(fds3);
            
            if (fork())
            {
                dup2(fds3[1], 1);
                close(fds3[0]);
                close(fds3[1]);
                execlp("uniq", "uniq", NULL);
            }
            else
            {
                close(fds1[0]);
                close(fds2[0]);
                dup2(fds3[0], 0);
                close(fds3[0]);
                close(fds3[1]);
                execlp("wc", "wc", "-l", NULL);
            }
        }
    }

    return 0;
}
