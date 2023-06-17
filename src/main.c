#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

int main(void) {
    Arvore *arvore = inicializa_arvore();

    inserir_letra(arvore, ".-", 'A');
    inserir_letra(arvore, ".", 'E');
    inserir_letra(arvore, "-...", 'B');

    char c = conv_morse_para_char(arvore, ".-");
    printf("%c \n", c);
    assert(c == 'A');

    c = conv_morse_para_char(arvore, ".");
    printf("%c \n", c);
    assert(c == 'E');

    c = conv_morse_para_char(arvore, "-...");
    printf("%c \n", c);
    assert(c == 'B');

    printf("Inicio teste caminhamento por profundidade\n");
    profundidade(arvore);

    printf("Inicio teste conversão de char para morse\n");
    char *morse = conv_char_para_morse(arvore, 'B');
    printf("B = %s\n", morse);
    assert(strcmp("-...", morse) == 0);
    free(morse);

    desalocar_arvore(arvore);

    return 0;
}
