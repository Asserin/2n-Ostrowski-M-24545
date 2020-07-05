#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	//Otwórz plik tylko do odczytu
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("COULDN'T OPEN THE FILE");
        return -1;
    }
	//Odczyta wartości, pomnoży przez 3 i pokażę wynik
    int value;
    for (int i = 0; i < 10; i++)
    {
        read(fd, &value, sizeof(8));
        printf("%d * 3 = %d\n", value, value * 3);
    }

    return 0;
}

