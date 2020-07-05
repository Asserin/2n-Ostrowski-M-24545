#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

    //Tworzy tablice na 10 elementów
    int rand_nums[10];
	//Tworzy plik tylko do zapisu
    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("Couldn't create the file");
        return -1;
    }
    //Generuje losowe numery
    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < 10; i++)
    {
        rand_nums[i] = rand() % 100;
        printf("%d, ", rand_nums[i]);
    }
	//Zapisuje tablice w danym pliku fd
    write(fd, rand_nums, sizeof(rand_nums));
    return 0;
}
