#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "../include/client.h"

#define MAX_TOTAL_ARGS_LENGTH 300 //o tamanho total dos argumentos passados à opção execute não excede os 300 bytes
#define MAX_BUFFER_SIZE 1024 
#define SERVER_FIFO "../tmp/Server_fifo"

int main(int argc, char *argv[]) {
    int server_fifo = open("../tmp/Server_fifo", O_WRONLY);
    char buffer[MAX_BUFFER_SIZE];
    int read_bytes;

    char client_fifo_name[50];
    sprintf(client_fifo_name, "../tmp/client_fifo_%d", getpid());

    if(mkfifo(client_fifo_name, 0640) < 0){
        printf("Fifo already exists\n");
    }

    while ((read_bytes = read(STDIN_FILENO,buffer,MAX_BUFFER_SIZE))>0){
        write(server_fifo,buffer,read_bytes);
    }

    // //caso meta o comando errado mostra quais são os comandos certos
    // if (argc < 2) {
    //     fprintf(stderr, "Use: client [comando]\n");
    //     fprintf(stderr, "Comandos disponíveis:\n");
    //     fprintf(stderr, "  - Para submeter uma tarefa: client execute tempo_estimado programa [argumentos...]\n");
    //     fprintf(stderr, "  - Para consultar o status: client status\n");
    //     exit(1);

    // }

    // // Verificar o comando fornecido
    // if (strcmp(argv[1], "status") == 0) {
    //     //temos de ver como vamos enviar pó servidor

    // } else if (strcmp(argv[1], "execute") == 0) {
    //     // Comando execute time -u "prog-a [args]"
    //     if (argc < 5) {
    //         fprintf(stderr, "Erro: O comando \"execute\" requer pelo menos 3 argumentos.\n");
    //         exit(1);
    //     }

    //     // Verificar tamanho total dos argumentos
    //     int total_args_length = 0;
    //     for (int i = 4; i < argc; i++) {
    //         total_args_length += strlen(argv[i]) + 1; // +1 para o espaço entre argumentos
    //     }
    //     if (total_args_length > MAX_TOTAL_ARGS_LENGTH) {
    //         fprintf(stderr, "Erro: Tamanho total dos args é superior a 300bytes.\n");
    //         exit(EXIT_FAILURE);
    //     }

    //     // Pegar nos parâmetros
    //     int tempo_estimado = atoi(argv[2]); //TODO: GARANTIR QUE O TEMPO NAO É INFERIOR A ZERO ms
    //     char *programa = argv[3];
    //     char argumentos[MAX_TOTAL_ARGS_LENGTH] = "";
    //     for (int i = 4; i < argc; i++) {
    //         strcat(argumentos, argv[i]);
    //         strcat(argumentos, " ");
    //     }

    //     // Nome único para o FIFO do cliente
    //     char fifo_name[50];
    //     sprintf(fifo_name, "fifo_cliente_%d", getpid()); //getpid() dà-me o meu numero assim,com o pid do cliente garantimos de cada FIFO tem um nome único

    //     // Criar o FIFO do cliente para ele receber as respostas do cliente
    //     int mkfifo_result = mkfifo(fifo_name, 0644);
    //     if (mkfifo_result == -1) {
    //         perror("Erro ao criar o FIFO do cliente");
    //         exit(1);
    //     }

    //     // Abrir o FIFO do servidor para escrita
    //     int fd = open("pipe_servidor", O_WRONLY);
    //     if (fd == -1) {
    //         perror("Erro ao abrir o pipe do servidor");
    //         exit(1);
    //     }

    //     // Enviar solicitação para o servidor
    //     dprintf(fd, "%d:%s:%s:%s\n", tempo_estimado, programa, argumentos, fifo_name);

    //     // Fechar o FIFO do servidor
    //     close(fd);

    //     // Abrir o FIFO do cliente para leitura
    //     fd = open(fifo_name, O_RDONLY);
    //     if (fd == -1) {
    //         perror("Erro ao abrir o FIFO do cliente");
    //         exit(EXIT_FAILURE);
    //     }

    //     // Ler e imprimir a resposta do servidor
    //     char buffer[MAX_BUFFER_SIZE];
    //     ssize_t bytes_read;
    //     while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
    //         write(STDOUT_FILENO, buffer, bytes_read);
    //     }

    //     // Fechar o FIFO do cliente
    //     close(fd);

    //     // Remover o FIFO do cliente
    //     unlink(fifo_name);

    // } else {
    //     fprintf(stderr, "Erro: Comando \"%s\" não reconhecido.\n", argv[1]);
    //     exit(EXIT_FAILURE);
    // }

    return 0;
}
