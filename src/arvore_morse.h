#ifndef ARVORE_MORSE_H
#define ARVORE_MORSE_H
#define TAM_MAX_MORSE 6

// Enum para definir caracteres usados no morse e a representação de um nó vazio
typedef enum codificacao {
    PONTO = '.',
    TRACO = '-',
    VAZIO = '\0'
} codificacao_morse;

// Definição da estrutura de cada nó da árvore
typedef struct node {
    char caracter;
    struct node *esq;
    struct node *dir;
    char morse[TAM_MAX_MORSE];
} node;

typedef struct node ArvoreMorse;

// Insere nova letra na árvore, criando o respectivo nó
void inserir_letra(ArvoreMorse *arvore_morse, char *cod_morse, char letra);

// Inicializa árvore com um nó vazio, utilizado para criar o nó raiz
node *inicializa_arvore();

// Imprime árvore utilizando caminhamento pré-ordem
void imprime_arvore_pre_ordem(ArvoreMorse *arvore_morse);

// Converse um respectivo código morse para seu alfanumérico correspondente caso exista na árvore
char conv_morse_para_char(ArvoreMorse *arvore_morse, char *cod_morse);

/*Converte um respectivo caracter alfanumérico para seu codigo morse correspondente. Deve-se liberar a memória da string retornada futuramente*/
char *conv_char_para_morse(ArvoreMorse *arvore_morse, char letra);

// Libera totalmente a memória consumida pela árvore
void desalocar_arvore(ArvoreMorse *arvore_morse);

// Preenche árvore com os dados padrões pre-estabelecidos na documentação
void preenche_arvore(ArvoreMorse *arvore_morse);

/*Recebe uma string em alfanumérico e a retorna convertida para morse. Deve se liberar a memória da string retornada futuramente*/ 
char *converte_str_alfa_para_morse(char *str_recebida, ArvoreMorse *arvore_morse);

/*Recebe uma string em morse e a retorna convertida para alfanumérico. Deve se liberar a memória da string retornada futuramente*/
char *converte_str_morse_para_alfa(char *str_recebida, ArvoreMorse *arvore_morse);

// Cria um nó e atribui a respectiva letra no nó correspondente
node *criar_no(char letra);

#endif
