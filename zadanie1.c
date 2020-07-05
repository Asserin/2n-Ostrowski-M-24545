#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1
//Funkcja, która dodaje .red do nazwy pliku
char *get_file_name(char *file);

int main(int argc, char *argv[])
{
    //Vars
    int input_fd, output_fd;
    char buffer[BUFFER_SIZE];
    ssize_t ret_in, ret_out;
	//Sprawdzanie czy user podał miejsce docelowe pliku
    if (argc != 2)
    {
        printf("Not enough elements");
        return -1;
    }
	//Otwiera podany plik tylko do odczytu i sprawdza pod kątem błędu
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
    {
        perror("open");
        return -1;
    }
	//Tworzy nową nazwę pliku za pomocą .red
    char *new_file_name = get_file_name(argv[1]);
	//Utworzy plik wyjściowy i sprawdzi czy występują błędy
    output_fd = open(new_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (output_fd == -1)
    {
        perror("write");
        return -1;
    }
	//Pobiera co trzeci element za pomocą Iseek() danego pliku i zapisuje do pliku wyjściowego
    while ((ret_in = read(input_fd, &buffer, BUFFER_SIZE)) > 0)
    {
        lseek(input_fd, 2, SEEK_CUR);
        ret_out = write(output_fd, &buffer, BUFFER_SIZE);
    }

    close(input_fd);
    close(output_fd);
    return 0; 
}

char *get_file_name(char *file)
{
    char *file_name = strtok(file, ".");
    char *new_file_name = strcat(file_name, ".red.txt");

    return new_file_name;
}
