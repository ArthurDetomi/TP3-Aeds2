#include "arvore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PONTO '.'
#define TRACO '-'

void verifica_se_alocacao_falhou(void *pont_gen) {
    if (pont_gen == NULL) {
        printf("Erro: falta de memoria\n");
        exit(1);
    }
}

node *inicializa_arvore() {
    return criar_no(-1);
}

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
            if (no_atual->dir == NULL) { no_atual->dir = criar_no('-'); }
            no_atual = no_atual->dir;
        } else if (cod_morse[i] == PONTO) {
            if (no_atual->esq == NULL) { no_atual->esq = criar_no('.'); }
            no_atual = no_atual->esq;
        }
    }

    no_atual->caracter = letra;
    strcpy(no_atual->morse, cod_morse);
}

char conv_morse_para_char(Arvore *arvore, char *cod_morse) {
    int tam_codigo = strlen(cod_morse);
    if (tam_codigo <= 0 || tam_codigo > 5) { printf("Erro: Cod_morse inválido\n"); }

    char c = -1;
    for (int i = 0; i < tam_codigo; i++) {
        if (cod_morse[i] == TRACO) {
            if (arvore->dir == NULL) {
                printf("Erro: codigo nao encontrado\n");
                return -1;
            }
            arvore = arvore->dir;
        } else if (cod_morse[i] == PONTO) {
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

void profundidade(Arvore *arvore) {
    if (arvore != NULL) {
        printf("%c\n", arvore->caracter);
        profundidade(arvore->esq);
        profundidade(arvore->dir);
    }
}

char *conv_char_para_morse(Arvore *arvore, char letra) {
    if (arvore == NULL) { return NULL; }

    if (arvore->caracter == letra) {
        char *morse_procurado = (char *)malloc(strlen(arvore->morse + 1));
        strcpy(morse_procurado, arvore->morse);
        return morse_procurado;
    }

    char *morse_procurado = conv_char_para_morse(arvore->esq, letra);
    if (morse_procurado != NULL) { return morse_procurado; }

    morse_procurado = conv_char_para_morse(arvore->dir, letra);
    if (morse_procurado != NULL) { return morse_procurado; }

    return NULL;
}
