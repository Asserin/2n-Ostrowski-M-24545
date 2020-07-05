#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    pid = fork();

    if (pid > 0)
    {
        int status;
        wait(&status);
        printf("Child proces done with: %d\n!", status);
    }
    if (pid == 0)
    {
        //Tworzy tablice
        int array[31];
        int startVal = 9;
        int finishVal = 99;
        //Przypisuje wartości do tablicy
        int i = 0;
        while (startVal <= finishVal)
        {
            if (startVal % 3 == 0)
            {
                array[i] = startVal;
                i++;
            }
            startVal++;
        }

        //Tworzy i otwiera plik
        FILE *f;

        f = fopen("range.txt", "w+");
        if (f == NULL)
        {
            _exit(1);
        }

        //Zapisuje do pliku
        for (int i = 0; i <= 30; i++)
        {
            fputc(array[i], f);
        }

        //Zamyka plik
        fclose(f);
        printf("Child fineshed!\n");
        _exit(0);
    }
    if (pid < 0)
    {
        _exit(1);
    }

    return 0;
}
