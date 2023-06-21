#include "arvore_morse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_MAX_STR 5
#define TAM_BUFFER 140

int main(int argv, char *argc[]) {
    if (argv != 3) {
        printf("Error: argumentos invalidos\n");
        return 1;
    }

    FILE *arquivo = fopen(argc[1], "r");
    if (arquivo == NULL) {
        perror("Error");
        return 1;
    }
    ArvoreMorse *arvore_morse = inicializa_arvore();
    preenche_arvore(arvore_morse);

    if (strcmp("-a", argc[2]) == 0) {
        printf("Escolha: Conversao de asc2 para morse :\n");

        char str_buffer[TAM_BUFFER];
        while (!feof(arquivo)) {
            if (fgets(str_buffer, TAM_BUFFER, arquivo) != NULL) {
                if (str_buffer[0] != '\n') {
                    char *str_convertida
                        = converte_str_alfa_para_morse(str_buffer, arvore_morse);
                    if (str_convertida != NULL) {
                        printf("%s\n", str_convertida);
                        free(str_convertida);
                        str_convertida = NULL;
                    }
                }
            }
        }
        printf("\n");
    }
    else if (strcmp("-m", argc[2]) == 0) {
        printf("Escolha: Conversao de Morse para asc2:\n");
    }
    else {
        printf("Error: argumentos invalidos\n");
        return 1;
    }

    desalocar_arvore(arvore_morse);
    fclose(arquivo);
    arquivo = NULL;
    return 0;
}
