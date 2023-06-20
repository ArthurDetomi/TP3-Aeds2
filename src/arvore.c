#include "arvore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_MAX_STR 5

void verifica_se_alocacao_falhou(void *pont_gen) {
    if (pont_gen == NULL) {
        printf("Erro: falta de memoria\n");
        exit(1);
    }
}

node *inicializa_arvore() { return criar_no('\0'); }

node *criar_no(char letra) {
    node *novo_no = (node *)malloc(sizeof(node));
    verifica_se_alocacao_falhou(novo_no);
    novo_no->caracter = letra;
    novo_no->dir = NULL;
    novo_no->esq = NULL;
    return novo_no;
}

void inserir_letra(Arvore *arvore, char *cod_morse, char letra) {
    int tam_codigo = strlen(cod_morse);

    if (tam_codigo <= 0 || tam_codigo > 5) {
        printf("Erro: Morse nao inserido\n");
        return;
    }

    node *no_atual = arvore;
    for (int i = 0; i < tam_codigo; i++) {
        if (cod_morse[i] == TRACO) {
            if (no_atual->dir == NULL) {
                no_atual->dir = criar_no('-');
            }
            no_atual = no_atual->dir;
        }
        else if (cod_morse[i] == PONTO) {
            if (no_atual->esq == NULL) {
                no_atual->esq = criar_no('.');
            }
            no_atual = no_atual->esq;
        }
    }

    no_atual->caracter = letra;
    strcpy(no_atual->morse, cod_morse);
}

char conv_morse_para_char(Arvore *arvore, char *cod_morse) {
    int tam_codigo = strlen(cod_morse);
    if (tam_codigo <= 0 || tam_codigo > 5) {
        printf("Erro: Cod_morse inválido\n");
    }

    char c = -1;
    for (int i = 0; i < tam_codigo; i++) {
        if (cod_morse[i] == TRACO) {
            if (arvore->dir == NULL) {
                printf("Erro: codigo nao encontrado\n");
                return -1;
            }
            arvore = arvore->dir;
        }
        else if (cod_morse[i] == PONTO) {
            if (arvore->esq == NULL) {
                printf("Erro: codigo nao encontrado\n");
                return -1;
            }
            arvore = arvore->esq;
        }
    }

    c = arvore->caracter;
    return c;
}

void imprime_arvore_pre_ordem(Arvore *arvore) {
    if (arvore != NULL) {
        if (!(arvore->caracter == '.' || arvore->caracter == '-'
              || arvore->caracter == '\0'))
        {
            printf("%c\n", arvore->caracter);
        }
        imprime_arvore_pre_ordem(arvore->esq);
        imprime_arvore_pre_ordem(arvore->dir);
    }
}

char *conv_char_para_morse(Arvore *arvore, char letra) {
    if (arvore == NULL) {
        return NULL;
    }

    if (arvore->caracter == letra) {
        char *morse_procurado = (char *)malloc(strlen(arvore->morse + 1));
        strcpy(morse_procurado, arvore->morse);
        return morse_procurado;
    }

    char *morse_procurado = conv_char_para_morse(arvore->esq, letra);
    if (morse_procurado != NULL) {
        return morse_procurado;
    }

    morse_procurado = conv_char_para_morse(arvore->dir, letra);
    if (morse_procurado != NULL) {
        return morse_procurado;
    }

    return NULL;
}

void libera_no(node *no) {
    if (no == NULL) {
        return;
    }
    libera_no(no->esq);
    libera_no(no->dir);
    free(no);
    no = NULL;
}

void desalocar_arvore(Arvore *arvore) {
    if (arvore == NULL) {
        return;
    }
    libera_no(arvore);
    arvore = NULL;
}

void preenche_arvore(Arvore *arvore) {
    inserir_letra(arvore, ".-", 'a');
    inserir_letra(arvore, "-...", 'b');
    inserir_letra(arvore, "-.-.", 'c');
    inserir_letra(arvore, "-..", 'd');
    inserir_letra(arvore, ".", 'e');
    inserir_letra(arvore, "..-.", 'f');
    inserir_letra(arvore, "--.", 'g');
    inserir_letra(arvore, "....", 'h');
    inserir_letra(arvore, "..", 'i');
    inserir_letra(arvore, ".---", 'j');
    inserir_letra(arvore, "-.-", 'k');
    inserir_letra(arvore, ".-..", 'l');
    inserir_letra(arvore, "--", 'm');
    inserir_letra(arvore, "-.", 'n');
    inserir_letra(arvore, "---", 'o');
    inserir_letra(arvore, ".--.", 'p');
    inserir_letra(arvore, "--.-", 'q');
    inserir_letra(arvore, ".-.", 'r');
    inserir_letra(arvore, "...", 's');
    inserir_letra(arvore, "-", 't');
    inserir_letra(arvore, "..-", 'u');
    inserir_letra(arvore, "...-", 'v');
    inserir_letra(arvore, ".--", 'w');
    inserir_letra(arvore, "-..-", 'x');
    inserir_letra(arvore, "-.--", 'y');
    inserir_letra(arvore, "--..", 'z');
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
        inserir_letra(arvore, morse, (char)i + '0');
    }
}

char *converte_str_alfa_para_morse(char *str_recebida, int opcao, Arvore *arvore) {
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

                char carac_split = (char) tolower(str_split[i]);  
                char *morse_resultado = conv_char_para_morse(arvore, carac_split);

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