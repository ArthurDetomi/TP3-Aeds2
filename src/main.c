#include "arvore_morse.h"
#include "msgs_programa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_MAX_STR 5
#define TAM_BUFFER 140
#define QTD_MAX_ARGS 3

int main(int argv, char *argc[]) {
    // Argumentos existentes no programa
    char alfa_para_morse[] = "-a";
    char morse_para_alfa[] = "-m";
    char imprimir_arvore_morse[] = "-i";

    if (argv <= 1) {
        printf("Error: Nenhum argumento passado\n");
        return ERRO_QTD_ARGS_INVALIDA;
    }

    // Inicializa arvore morse para conversões
    ArvoreMorse *arvore_morse = inicializa_arvore();
    preenche_arvore(arvore_morse);

    // Imprime arvore e finaliza programa, caso entre no if
    if (strcmp(argc[1], imprimir_arvore_morse) == 0 && argv < QTD_MAX_ARGS) {
        printf("Imprimindo Arvore Morse:\n");
        printf("%5s | %5s\n", "Caracter", "Morse");
        imprime_arvore_pre_ordem(arvore_morse);
        return PROGRAMA_EXECUTADO_COM_SUCESSO;
    }

    // Qtd de argumentos invalidos, finaliza programa
    if (argv != QTD_MAX_ARGS) {
        printf("Error: argumentos invalidos\n");
        return ERRO_QTD_ARGS_INVALIDA;
    }
    
    FILE *arquivo = fopen(argc[1], "r");
    if (arquivo == NULL) {
        perror("Error");
        return ERRO_ARQ_INVALIDO;
    }

    if (strcmp(alfa_para_morse, argc[2]) == 0) {
        printf("Escolha: Conversao de asc2 para morse :\n");

        char str_buffer[TAM_BUFFER];
        while (!feof(arquivo)) {
            if (fgets(str_buffer, TAM_BUFFER, arquivo) != NULL) {
                if (str_buffer[0] != '\n') {
                    char *str_convertida = converte_str_alfa_para_morse(
                        str_buffer, arvore_morse
                    );
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
    else if (strcmp(morse_para_alfa, argc[2]) == 0) {
        printf("Escolha: Conversao de Morse para asc2:\n");

        char str_buffer[TAM_BUFFER];
        while (!feof(arquivo)) {
            if (fgets(str_buffer, TAM_BUFFER, arquivo) != NULL) {
                if (str_buffer[0] != '\n') {
                    char *str_convertida = converte_str_morse_para_alfa(
                        str_buffer, arvore_morse
                    );
                    if (str_convertida != NULL) {
                        printf("%s\n", str_convertida);
                        free(str_convertida);
                        str_convertida = NULL;
                    }
                }
            }
        }
    }
    else {
        printf("Error: argumentos invalidos\n");
        return ERRO_QTD_ARGS_INVALIDA;
    }

    desalocar_arvore(arvore_morse);
    fclose(arquivo);
    arquivo = NULL;
    return PROGRAMA_EXECUTADO_COM_SUCESSO;
}
