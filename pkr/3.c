#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char** argv)
{
    if (argc < 3)
        return 1;

    // ако нямаме подадени файлове като аргументи, четем от стандартния вход
    if (argc == 3)
        execlp("tr", "tr", argv[1], argv[2], NULL);

    for (int i = 3; i < argc; i++)
        // кодът вътре във `fork`-а се изпълнява асинхронно в друг процес
        if (!fork())
        {
            // пренасочваме стандартния вход към поредния файл
            close(0);
            open(argv[i], O_RDONLY);

            execlp("tr", "tr", argv[1], argv[2], NULL);
        }

    // изчакваме всички новосъздадени процеси да приключат работата си
    for (int i = 3; i < argc; i++)
    {
        int status;
        wait(&status);
    }

    return 0;
}
