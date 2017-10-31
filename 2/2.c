#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char* const* argv)
{
    if (argc < 2)
        return 1;

    int fd = open(argv[1], O_WRONLY | O_APPEND);
    lseek(fd, 0, SEEK_SET);
    write(fd, "foo", 3);
    return 0;
}
