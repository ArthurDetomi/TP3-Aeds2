#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

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
}
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
    profundidade(arvore);

    printf("Inicio teste conversão de char para morse\n");
    char *morse = conv_char_para_morse(arvore, 'b');
    printf("B = %s\n", morse);
    assert(strcmp("-...", morse) == 0);
    free(morse);

    desalocar_arvore(arvore);

    return 0;
}
