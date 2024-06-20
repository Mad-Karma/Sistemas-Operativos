
//server

// ----
// Estruturas de dados
// ----
// Estrutura de um processo a ser guardado
typedef struct process
{
    char *pid;         // PID do processo
    char *comando;     // Comando a executar
    int pipe_escrever; // Pipe para escrever
    
} Process;

// Queue onde serão armazenados os processos em espera
typedef struct queue
{
    int first, last, size; // Primeiro, último e tamanho da queue
    int capacity;          // Capacidade máxima da queue
    Process *processes;    // Array de processos
} Queue;