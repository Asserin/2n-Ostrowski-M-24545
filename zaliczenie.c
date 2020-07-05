#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	//Sprawdza, czy podano ściężkę do pliku.
    if (argc != 2)
    {
        printf("Brakujacy plik");
        return -1;
    }
	//Zapisyuje nazwy pliku do var.
    char *fname = argv[1];
	//Podział programu na dwa procesy.
    pid_t pid = fork(); //Proces ID - PID / Istniejący proces rodzica (parent) duplikuje własną przestrzeń adresową (fork), aby stworzyć nową strukturę procesu dla dziecka (child).

    if (pid > 0)
    {
        //Rodzic (parent)
		
		//Czeka aż proces dziecka (child) się zakończy.
        int wstatus;
        wait(&wstatus);
		
		//Sprawdzanie czy proces dziecka (child) zakończył się poprawnie.
        if (WIFEXITED(wstatus)) // WIFEXITED(wstatus) zwraca wartość zakończenia procesu (exit code). Powinno być używane tylko jeśli makro WIFEXITED(wstatus) zwróciło true.
        {
            //Wyświetlenie otrzymanego statusu.
            int wexstatus = WEXITSTATUS(wstatus);
            printf("Proces dziecka zakończył się ze statusem: %d. Program zakończył się powodzeniem.", wexstatus);
        }
    }
    else if (pid == 0)
    {
        //Dziecko (child)
        int input_fd, ssize, pid;
        char buff[100];

        //Otwiera plik.
        input_fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644); // 0644: user może odczytywać i zapisywać, grupy i inni tylko odczytać.
		//Funkcja open() pozwala na tworzenie plików i ustawienie jego tryby zarówno do zapisu jak i do odczytu. 
		//Funkcja creat() pozwala tylko na zapis.

        //Zapisuje do pliku
        for (int i = 0; i < 10; i++)
        {
            //Bierze Proces ID - PID.
            pid = (int)getpid();
			
			//Uzyskuje rozmiar polecenia i zapisuje go w bufforze.
            ssize = snprintf(buff, sizeof(buff), "Wywołanie nr %d. Numer procesu %d", i, pid); 
			//snprintf formatuje i przechowuję serię znaków i wartości w bufforze tablicy.
			//Funkcja snprintf z dodatkiem argumentu n, który wskazuje maksymalną liczbę znaków (w tym na końcu null) do zapisania w bufforze.

			//Zapisz do input_fd z buffera rozmiaru polecenia.
            write(input_fd, buff, ssize);
        }
        //Proces kończy się ze statusem 10.
        _Exit(10);
    }
	//Sprawdza pod kątem błędów.
    else
    {
        perror("Błąd");
        _Exit(-1);
    }

    return 0;
}