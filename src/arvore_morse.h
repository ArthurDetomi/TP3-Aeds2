#ifndef ARVORE_MORSE_H
#define ARVORE_MORSE_H
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

typedef struct node ArvoreMorse;

void inserir_letra(ArvoreMorse *arvore_morse, char *cod_morse, char letra);
node *criar_no(char caracter);
node *inicializa_arvore();
void imprime_arvore_pre_ordem(ArvoreMorse *arvore_morse);
char conv_morse_para_char(ArvoreMorse *arvore_morse, char *cod_morse);
char *conv_char_para_morse(ArvoreMorse *arvore_morse, char letra);
void desalocar_arvore(ArvoreMorse *arvore_morse);
void preenche_arvore(ArvoreMorse *arvore_morse);
char *converte_str_alfa_para_morse(char *str_recebida, ArvoreMorse *arvore_morse);

#endif
