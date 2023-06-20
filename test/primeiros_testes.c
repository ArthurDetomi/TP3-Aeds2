#include <stdio.h>
#include <string.h>

#include "../src/arvore.h"

int main(void) {
    Arvore *arvore = inicializa_arvore();
    preenche_arvore(arvore);

    char c = conv_morse_para_char(arvore, ".-");
    printf("%c \n", c);
    assert(c == 'a');

    c = conv_morse_para_char(arvore, ".");
    printf("%c \n", c);
    assert(c == 'e');

    c = conv_morse_para_char(arvore, "-...");
    printf("%c \n", c);
    assert(c == 'b');

    printf("Inicio teste caminhamento por profundidade\n");
    imprime_arvore_pre_ordem(arvore);

    printf("Inicio teste conversão de char para morse\n");
    char *morse = conv_char_para_morse(arvore, 'b');
    printf("B = %s\n", morse);
    assert(strcmp("-...", morse) == 0);
    free(morse);

    desalocar_arvore(arvore);

    return 0;
}