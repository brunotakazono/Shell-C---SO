#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define True 1
#define BUFFSIZE 512

int main() {
    char comando[BUFFSIZE];
    int status;

    while (True) {
        printf("Digite um comando (ou 'exit' para sair): ");

        if (fgets(comando, sizeof(comando), stdin) == NULL) {
            perror("Erro ao ler o comando");
            continue;
        }

        comando[strcspn(comando, "\n")] = '\0';

        if (strcmp(comando, "exit") == 0) {
            break;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("Erro ao criar um processo filho");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            execl("/bin/bash", "/bin/bash", "-c", comando, NULL);

            perror("Erro");
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                printf("Processo filho terminou com código de saída: %d\n", WEXITSTATUS(status));
            }
        }
    }

    return 0;
}
