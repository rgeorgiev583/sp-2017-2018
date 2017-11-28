#include <unistd.h>

void redirect(int fds[2], int redirect_fd)
{
    dup2(fds[redirect_fd], redirect_fd);
    close(fds[0]);
    close(fds[1]);
}

int main(int argc, char** argv)
{
    int fds[2];
    pipe(fds);

    if (!fork())
    {
        redirect(fds, 1);
        execlp(argv[1], argv[1], NULL);
    }

    for (int i = 2; i < argc - 1; i++)
    {
        if (!fork())
        {
            redirect(fds, 0);
            pipe(fds);
            redirect(fds, 1);
            execlp(argv[i], argv[i], NULL);
        }
    }

    if (!fork())
    {
        redirect(fds, 0);
        execlp(argv[argc - 1], argv[argc - 1], NULL);
    }

    return 0;
}
