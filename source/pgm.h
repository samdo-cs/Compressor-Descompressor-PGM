/******************************************************/
/* Aluno: Gabriel ícaro Barbosa Rocha                 */
/* Matricula: 20232045050155                          */
/* Aluno: Isaac de Brito Azevedo                      */
/* Matricula: 20232045050520                          */
/* Avaliacão 04: Trabalho Final                       */
/* 04.505.23 – 2024.1 – Prof. Daniel Ferreira         */
/* Compilador: GCC (MinGW.org GCC-6.3.0-1) 6.3.0      */
/******************************************************/

#ifndef PGM_H
#define PGM_H

#include <stdio.h>  // Necessário para o uso de FILE

struct pgm {
    int tipo;
    int c;    // Valor largura (colunas)
    int r;    // Valor altura (linhas)
    int mv;   // Valor máximo de intensidade
    unsigned char *pData;// Bitstream
};

// Funções de manipulação de PGM (compressão)

void lerPGM(struct pgm *, char *);
void salvarCabecalho(struct pgm *, FILE *);

// Funções de manipulação de PGM (descompressão)

void lerCabecalho(struct pgm *, FILE *);
void escreverImagemPGM(struct pgm *, char *);

#endif