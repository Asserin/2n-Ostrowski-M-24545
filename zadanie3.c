#include <stdio.h>
#include <errno.h>
#include <string.h>
//Funkcja, która tworzy plik z .red
char *get_file_name(char *file)
{
    char *file_name = strtok(file, ".");
    char *new_file_name = strcat(file_name, ".red.txt");

    return new_file_name;
}

int main(int argc, char *argv[])
{
    //Vars
    FILE *file_to_read, *file_to_write;
    char ch;
	//Otworzy plik do odczytu i sprawdzi pod kątem błędów
    file_to_read = fopen(argv[1], "r");
    if (file_to_read == NULL)
    {
        perror("Couldn't open the file!");
        return 1;
    }
	//Edytuje nazwę pliku aby dodać .red
    char *file_name = get_file_name(argv[1]);
	//Utworzy plik i otworzy go do zapisu i sprawdzi czy występują błędy
    file_to_write = fopen(file_name, "w+");
    if (file_to_write == NULL)
    {
        perror("Couldn't create a file!");
        return 1;
    }
	//Pętlka, która zapisuje do pliku co trzeci znak
    int index = 0;
    while (!feof(file_to_read))
    {
        ch = fgetc(file_to_read);

        if (index % 3 == 0)
        {
            fputc(ch, file_to_write);
        }
        index++;
    }
    printf("Writing succesfull!\n");
	//Zamyka wszystkie pliki i kończy program
    fclose(file_to_write);
    fclose(file_to_read);
    return 0;
}
