#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("wat", O_RDWR | O_CREAT | O_TRUNC, 0644);
    write(fd, "foo bar baz", 11);
    char buf[3];
    lseek(fd, 0, SEEK_SET);
    read(fd, buf, 3);
    write(1, buf, 3);
    lseek(fd, 1, SEEK_CUR);
    read(fd, buf, 3);
    write(1, buf, 3);
    lseek(fd, -3, SEEK_CUR);
    read(fd, buf, 3);
    write(1, buf, 3);
    lseek(fd, -7, SEEK_END);
    read(fd, buf, 3);
    write(1, buf, 3);
    lseek(fd, 4, SEEK_SET);
    read(fd, buf, 3);
    write(1, buf, 3);
    lseek(fd, 3, SEEK_END);
    write(fd, "pesho", 5);
    return 0;
}
