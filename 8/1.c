#include <unistd.h>

int main()
{
    int fds[2];
    pipe(fds);

    if (fork())
    {
        dup2(fds[1], 1);
        close(fds[0]);
        close(fds[1]);
        execlp("who", "who", NULL);
    }
    else
    {
        dup2(fds[0], 0);
        close(fds[0]);
        close(fds[1]);
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}
