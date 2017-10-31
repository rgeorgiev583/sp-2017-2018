#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("pesho", O_RDWR);
    char buf[3];
    lseek(fd, 8, SEEK_SET);
    read(fd, buf, 3);
    write(1, buf, 3);
    lseek(fd, -3, SEEK_CUR);
    read(fd, buf, 3);
    write(1, buf, 3);
    lseek(fd, -10, SEEK_END);
    read(fd, buf, 3);
    write(1, buf, 3);
    lseek(fd, 3, SEEK_END);
    write(fd, "quux", 4);
    return 0;
}
