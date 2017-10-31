#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char* const* argv)
{
    if (argc < 3)
        return 1;

    int fdi = open(argv[1], O_RDONLY);
    int fdo = creat(argv[2], 0644);

    char buf;
    size_t num_zeros = 0;
    while (read(fdi, &buf, 1) > 0)
    {
        if (buf != '\0')
        {
            if (num_zeros > 0)
            {
                lseek(fdo, num_zeros, SEEK_CUR);
                num_zeros = 0;
            }

            write(fdo, &buf, 1);
        }
        else
            num_zeros++;
    }

    return 0;
}
