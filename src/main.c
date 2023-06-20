#include "arvore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_MAX_STR 5

int main(int argv, char *argc[]) {
    if (argv != 3) {
        printf("Error: argumentos invalidos\n");
        return 1; 
    }

    FILE *arquivo = fopen(argc[1],"r");
    if (arquivo == NULL) {
        perror("Error");
        return 1; 
    }
    
    if (strcmp("-a", argc[2]) == 0) {
        printf("Escolha: Conversao de asc2 para morse :\n");
        Arvore *arvore = inicializa_arvore();
        preenche_arvore(arvore);

        char str_buffer[140];
        while (!feof(arquivo)) {
            str_buffer[strcspn(str_buffer, "\n")] = '\0';
            if (fgets (str_buffer , 140 , arquivo) != NULL ) {
                if (str_buffer[0] != '\n') {
                    char *str_convertida = converte_str_alfa_para_morse(str_buffer, 0, arvore);
                    if (str_convertida != NULL) {    
                        printf("%s\n", str_convertida);
                        free(str_convertida);
                        str_convertida = NULL;
                    }
                }
            }
        }
        printf("\n");
    } else if (strcmp("-m", argc[2]) == 0) {
        printf("Escolha: Conversao de Morse para asc2:\n");
        
    } else {
        printf("Error: argumentos invalidos\n");
        return 1;
    }

    fclose(arquivo);
    arquivo = NULL;
    return 0;
}
