#include <unistd.h>
#include <fcntl.h>


int main(int argc, char** argv)
{
    if (argc < 5)
        return 1;

    // пренасочваме стандартния вход на процеса от файл
    close(0);
    open(argv[3], O_RDONLY);
    // пренасочваме стандартния изход на процеса към файл
    close(1);
    creat(argv[4], 0644);

    // пренасочванията на стандартния вход/изход се наследяват от процеса-дете
    execlp("tr", "tr", argv[1], argv[2], NULL);
}
