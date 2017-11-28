#include <unistd.h>

void redirect(int fds[2], int redirect_fd)
{
    dup2(fds[redirect_fd], redirect_fd);
    close(fds[0]);
    close(fds[1]);
}

int main(int argc, char** argv)
{
    int fds1[2];
    pipe(fds1);

    if (fork())
    {
        redirect(fds1, 1);
        argv[2] = argv[1];
        argv[0] = "head";
        argv[1] = "-n";
        execvp("head", argv);
    }
    else
    {
        redirect(fds1, 0);

        int fds2[2];
        pipe(fds2);

        if (fork())
        {
            redirect(fds2, 1);
            execlp("grep", "grep", argv[2], NULL);
        }
        else
        {
            close(fds1[0]);
            redirect(fds2, 0);
            execlp("wc", "wc", "-l", NULL);
        }
    }

    return 0;
}
