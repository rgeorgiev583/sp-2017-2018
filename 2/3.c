#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* const* argv)
{
    if (argc < 3)
        return 1;

    int base_arg = 1;
    bool do_lseek = false;

    if (!strcmp(argv[1], "-l"))
    {
        base_arg = 2;
        do_lseek = true;
    }
    
    int fd = do_lseek ? creat(argv[base_arg], 0644) : open(argv[base_arg], O_CREAT | O_WRONLY | O_APPEND, 0644);
    int num_bytes = atol(argv[base_arg + 1]);
    
    for (int i = 0; i < num_bytes; i++)
    {
        if (do_lseek)
            lseek(fd, 0, SEEK_END);

        write(fd, "x", 1);
    }

    return 0;
}
