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
        argv[0] = "grep";
        execvp("grep", argv);
    }
    else
    {
        redirect(fds1, 0);

        int fds2[2];
        pipe(fds2);

        if (fork())
        {
            redirect(fds2, 1);
            execlp("sort", "sort", NULL);
        }
        else
        {
            redirect(fds2, 0);

            int fds3[2];
            pipe(fds3);
            
            if (fork())
            {
                redirect(fds3, 1);
                execlp("uniq", "uniq", NULL);
            }
            else
            {
                redirect(fds3, 0);
                execlp("wc", "wc", "-l", NULL);
            }
        }
    }

    return 0;
}
