#ifndef MSGS_PROGRAMA_H
#define MSGS_PROGRAMA_H

typedef enum codigos_de_resposta {
    PROGRAMA_EXECUTADO_COM_SUCESSO = 0,
    ERRO_QTD_ARGS_INVALIDA = 1,
    ERRO_ARQ_INVALIDO = 2,
    ERRO_FALTA_MEMORIA = 3
} respostas_programa;

#endif