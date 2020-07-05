#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

FILE *f;
char *filename = "signals.txt";

static void sig_usr(int);

int main(void)
{
	//Tworzy plik i zapisuje PID
    f = fopen(filename, "w");
    int pid = (int)getpid();
    fprintf(f, "%d", pid);
    fputs("\n", f);
    fclose(f);
	//Sprawdza pod kątem błędów podczas nasłuchiwania sygnałów
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        perror("Can't catch signal!");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        perror("Can't catch signal!");
    }
    for (;;)
    {
        pause();
    }
}

static void sig_usr(int signo)
{

    if (signo == SIGUSR1)
    {
		//Dodaje PPID do pliku
        printf("\n Added PPID to file \n");
        f = fopen(filename, "a");
        int ppid = (int)getppid();
        fprintf(f, "%d", ppid);
        fputs("\n", f);
        fclose(f);
    }
    else if (signo == SIGUSR2)
    {
		//Czyści plik
        printf("\n Cleared file! \n");
        f = fopen(filename, "w");
        fclose(f);
    }
    else
    {
        perror("Recieved signal error!");
    }
}
