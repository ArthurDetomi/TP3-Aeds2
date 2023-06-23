#include "arvore_morse.h"
#include "msgs_programa.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_STR 5

/*Recebe um ponteiro qualquer e verifica se está nulo, útil para testar se
 alocação foi realizada com sucesso, caso dê erro finaliza programa*/
void verifica_se_alocacao_falhou(void *pont_gen) {
    if (pont_gen == NULL) {
        printf("Erro: falta de memoria\n");
        exit(ERRO_FALTA_MEMORIA);
    }
}

// Inicializa árvore, inicia com raiz com caracter nulo para identifica-la
node *inicializa_arvore() { return criar_no(VAZIO); }

// Aloca um novo nó atribui um caracter no respectivo e o retorna
node *criar_no(char letra) {
    node *novo_no = (node *)malloc(sizeof(node));
    verifica_se_alocacao_falhou(novo_no);
    novo_no->caracter = letra;
    novo_no->dir = NULL;
    novo_no->esq = NULL;
    return novo_no;
}

// Inseri letra na arvore, caso dê erro informa no console
void inserir_letra(ArvoreMorse *arvore_morse, char *cod_morse, char letra) {
    int tam_codigo = strlen(cod_morse);

    if (tam_codigo <= 0 || tam_codigo > 5) {
        printf("Erro: Morse nao inserido\n");
        return;
    }

    node *no_atual = arvore_morse;
    for (int i = 0; i < tam_codigo; i++) {
        if (cod_morse[i] == TRACO) {
            if (no_atual->dir == NULL) {
                no_atual->dir = criar_no(VAZIO);
            }
            no_atual = no_atual->dir;
        }
        else if (cod_morse[i] == PONTO) {
            if (no_atual->esq == NULL) {
                no_atual->esq = criar_no(VAZIO);
            }
            no_atual = no_atual->esq;
        }
    }

    no_atual->caracter = letra;
    strcpy(no_atual->morse, cod_morse);
}

// Converter um codigo morse para char, caso dê erro retorna -1
char conv_morse_para_char(ArvoreMorse *arvore_morse, char *cod_morse) {
    int tam_codigo = strlen(cod_morse);
    if (tam_codigo <= 0 || tam_codigo > 5) {
        printf("Erro: Cod_morse inválido\n");
    }

    char c = -1;
    for (int i = 0; i < tam_codigo; i++) {
        if (cod_morse[i] == TRACO) {
            if (arvore_morse->dir == NULL) {
                printf("Erro: codigo nao encontrado\n");
                return -1;
            }
            arvore_morse = arvore_morse->dir;
        }
        else if (cod_morse[i] == PONTO) {
            if (arvore_morse->esq == NULL) {
                printf("Erro: codigo nao encontrado\n");
                return -1;
            }
            arvore_morse = arvore_morse->esq;
        }
    }

    c = arvore_morse->caracter;
    return c;
}

// Imprimi os nós da arvore utilizando caminhamento pré ordem, ignora raiz e nós
// sem caracteres alfa
void imprime_arvore_pre_ordem(ArvoreMorse *arvore_morse) {
    if (arvore_morse != NULL) {
        if (arvore_morse->caracter != VAZIO) {
            printf(
                "%5c ->   %5s\n", arvore_morse->caracter, arvore_morse->morse
            );
        }
        imprime_arvore_pre_ordem(arvore_morse->esq);
        imprime_arvore_pre_ordem(arvore_morse->dir);
    }
}

// Recebe uma letra e retorna seu respectivo código morse
char *conv_char_para_morse(ArvoreMorse *arvore_morse, char letra) {
    if (arvore_morse == NULL) {
        return NULL;
    }

    if (arvore_morse->caracter == letra) {
        char *morse_procurado = (char *)malloc(strlen(arvore_morse->morse + 1));
        strcpy(morse_procurado, arvore_morse->morse);
        return morse_procurado;
    }

    char *morse_procurado = conv_char_para_morse(arvore_morse->esq, letra);
    if (morse_procurado != NULL) {
        return morse_procurado;
    }

    morse_procurado = conv_char_para_morse(arvore_morse->dir, letra);
    if (morse_procurado != NULL) {
        return morse_procurado;
    }

    return NULL;
}

// libera memória de um nó
void libera_no(node *no) {
    if (no == NULL) {
        return;
    }
    libera_no(no->esq);
    libera_no(no->dir);
    free(no);
    no = NULL;
}

// Desaloca toda memoria ocupada pela árvore
void desalocar_arvore(ArvoreMorse *arvore_morse) {
    if (arvore_morse == NULL) {
        return;
    }
    libera_no(arvore_morse);
    arvore_morse = NULL;
}

// Recebe uma string em alfa e a converte para morse
char *converte_str_alfa_para_morse(char *str_recebida, ArvoreMorse *arvore_morse) {
    int tam_str = strlen(str_recebida);
    if (tam_str == 0) {
        printf("Error: Arquivo vazio\n");
        exit(1);
    }

    unsigned int tam_str_final = sizeof(char) * tam_str * TAM_MAX_MORSE + 1;
    char *str_final = (char *)calloc(tam_str_final, sizeof(char));
    verifica_se_alocacao_falhou(str_final);

    char *str_split = strtok(str_recebida, " ");

    unsigned int qtd_caracteres_gravados = 0;
    while (str_split != NULL) {
        int tam_split = strlen(str_split);
        for (int i = 0; i < tam_split; i++) {
            if (str_split[i] != '\n') {
                if (qtd_caracteres_gravados == tam_str_final) {
                    tam_str_final = tam_str_final * 2;
                    str_final = (char *)realloc(str_final, tam_str_final);
                }

                char carac_split = (char)tolower(str_split[i]);
                char *morse_resultado
                    = conv_char_para_morse(arvore_morse, carac_split);

                if (morse_resultado != NULL) {
                    strcat(str_final, morse_resultado);
                    strcat(str_final, " ");
                    free(morse_resultado);
                }
            }

            qtd_caracteres_gravados += 2;
        }
        str_split = strtok(NULL, " ");
        if (str_split != NULL) {
            strcat(str_final, "/ ");
        }
    }
    return str_final;
}

// Recebe uma string em morse e a converte para alfa
char *converte_str_morse_para_alfa(char *str_recebida, ArvoreMorse *arvore_morse) {
    int tam_str = strlen(str_recebida);
    if (tam_str == 0) {
        printf("Error: Arquivo vazio\n");
        exit(1);
    }

    unsigned int tam_str_final = sizeof(char) * tam_str + 1;
    char *str_final = (char *)calloc(tam_str_final, sizeof(char));
    verifica_se_alocacao_falhou(str_final);

    char *str_split = strtok(str_recebida, " ");
    unsigned int qtd_caracteres_gravados = 0;
    while (str_split != NULL) {
        int tam_split = strlen(str_split);

        // Provavelmente não vai entrar nesse if mas é uma precaução
        if (qtd_caracteres_gravados == tam_str_final) {
            tam_str_final = tam_str_final * 2;
            str_final = (char *)realloc(str_final, tam_str_final);
            verifica_se_alocacao_falhou(str_final);
        }

        if (strcmp(str_split, "/") == 0) {
            str_final[qtd_caracteres_gravados] = ' ';
            qtd_caracteres_gravados++;
        }
        else if (strcmp(str_split, "\n") != 0) {
            char caracter_convertido
                = conv_morse_para_char(arvore_morse, str_split);

            if (caracter_convertido != -1) {
                str_final[qtd_caracteres_gravados] = caracter_convertido;
                qtd_caracteres_gravados++;
            }
        }

        str_split = strtok(NULL, " ");
    }
    str_final[qtd_caracteres_gravados] = '\0';
    return str_final;
}

// Preenche árvore com os cod_morse respectivo e a letra correspondente
void preenche_arvore(ArvoreMorse *arvore_morse) {
    inserir_letra(arvore_morse, ".-", 'a');
    inserir_letra(arvore_morse, "-...", 'b');
    inserir_letra(arvore_morse, "-.-.", 'c');
    inserir_letra(arvore_morse, "-..", 'd');
    inserir_letra(arvore_morse, ".", 'e');
    inserir_letra(arvore_morse, "..-.", 'f');
    inserir_letra(arvore_morse, "--.", 'g');
    inserir_letra(arvore_morse, "....", 'h');
    inserir_letra(arvore_morse, "..", 'i');
    inserir_letra(arvore_morse, ".---", 'j');
    inserir_letra(arvore_morse, "-.-", 'k');
    inserir_letra(arvore_morse, ".-..", 'l');
    inserir_letra(arvore_morse, "--", 'm');
    inserir_letra(arvore_morse, "-.", 'n');
    inserir_letra(arvore_morse, "---", 'o');
    inserir_letra(arvore_morse, ".--.", 'p');
    inserir_letra(arvore_morse, "--.-", 'q');
    inserir_letra(arvore_morse, ".-.", 'r');
    inserir_letra(arvore_morse, "...", 's');
    inserir_letra(arvore_morse, "-", 't');
    inserir_letra(arvore_morse, "..-", 'u');
    inserir_letra(arvore_morse, "...-", 'v');
    inserir_letra(arvore_morse, ".--", 'w');
    inserir_letra(arvore_morse, "-..-", 'x');
    inserir_letra(arvore_morse, "-.--", 'y');
    inserir_letra(arvore_morse, "--..", 'z');
    // inserir numeros caracteres numericos de 0 a 9
    char cod_atual_1 = '.';
    char cod_atual_2 = '-';
    int aux = 0;
    for (int i = 0; i < 10; i++) {
        char morse[TAM_MAX_STR];
        int tam = 0;
        for (int j = 0; j < TAM_MAX_STR; j++) {
            if (j < aux) {
                morse[j] = cod_atual_1;
            }
            else {
                morse[j] = cod_atual_2;
            }
            tam++;
        }
        aux++;
        morse[tam] = '\0';
        if (aux == TAM_MAX_STR) {
            cod_atual_1 = '-';
            cod_atual_2 = '.';
            aux = 0;
        }
        inserir_letra(arvore_morse, morse, (char)i + '0');
    }
}