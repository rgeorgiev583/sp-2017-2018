#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1000

int main(int argc, const char* const* argv)
{
    int base_arg = 1;
    bool do_append = false;

    if (argc > 1 && !strcmp(argv[1], "-a"))
    {
        base_arg = 2;
        do_append = true;
    }

    char buf[BUF_SIZE];
    int count;
    int* fds = malloc((argc - base_arg) * sizeof(int));

    for (int i = base_arg; i < argc; i++)
        fds[i] = do_append ? open(argv[i], O_WRONLY | O_APPEND, 0644) : creat(argv[i], 0644);

    while ((count = read(0, buf, BUF_SIZE)) > 0)
    {
        write(1, buf, count);

        for (int i = base_arg; i < argc; i++)
            if (!fork())
            {
                write(fds[i], buf, count);
                exit(0);
            }

        for (int i = base_arg; i < argc; i++)
        {
            int status;
            wait(&status);
        }
    }

    free(fds);
    return 0;
}
