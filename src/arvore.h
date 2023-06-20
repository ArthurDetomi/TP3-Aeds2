#ifndef ARVORE_H
#define ARVORE_H
#define TAM_MAX_MORSE 6

typedef enum codificacao {
    PONTO = '.',
    TRACO = '-'
} codificacao_morse;

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
void imprime_arvore_pre_ordem(Arvore *arvore);
char conv_morse_para_char(Arvore *arvore, char *cod_morse);
char *conv_char_para_morse(Arvore *arvore, char letra);
void desalocar_arvore(Arvore *arvore);
void preenche_arvore(Arvore *arvore);
char *converte_str_alfa_para_morse(char *str_recebida, int opcao, Arvore *arvore);

#endif
