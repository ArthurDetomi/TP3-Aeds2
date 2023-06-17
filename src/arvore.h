#ifndef ARVORE_H
#define ARVORE_H
#define TAM_MAX_MORSE 6

typedef struct node {
    char caracter;
    struct node *esq;
    struct node *dir;
    char morse[TAM_MAX_MORSE];
} node;

typedef struct node Arvore;

void inserir_letra(Arvore *arvore, char *cod_morse, char letra);
node *criar_no(char caracter);
node *inicializa_arvore();
void profundidade(Arvore *arvore);
char conv_morse_para_char(Arvore *arvore, char *cod_morse);
char *conv_char_para_morse(Arvore *arvore, char letra);

#endif
