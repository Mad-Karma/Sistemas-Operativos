#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 1024 

int main() {
    if(mkfifo("../tmp/Server_fifo",0640) < 0){
        printf("Fifo already exists\n");
    }

    int serverFifo = open("../tmp/Server_fifo", O_RDONLY, 0660);
    char buf[MAX_BUFFER_SIZE];
    int read_bytes;

    while ((read_bytes = read(serverFifo, buf, MAX_BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO,buf,read_bytes);
    }

    // while (1) {
    //     char command[300], clientFifo[256];

    //     if (read(serverFifo, command, sizeof(command)) > 0) {
    //         // Parsear o comando para obter o FIFO do cliente
    //         sscanf(command, "%*s %s", clientFifo);  // Ignorar o comando, ler só o FIFO
    //         close(serverFifo);

    //         // Processamento fictício
    //         char response[1024] = "Processado com sucesso";

    //         // Enviar resposta para o FIFO do cliente
    //         int fd = open(clientFifo, O_WRONLY);
    //         if (fd != -1) {
    //             write(fd, response, strlen(response));
    //             close(fd);
    //         }
    //     }
    // }

    return 0;
}