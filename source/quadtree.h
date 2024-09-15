/******************************************************/
/* Aluno: Gabriel ícaro Barbosa Rocha                 */
/* Matricula: 20232045050155                          */
/* Aluno: Isaac de Brito Azevedo                      */
/* Matricula: 20232045050520                          */
/* Avaliacão 04: Trabalho Final                       */
/* 04.505.23 – 2024.1 – Prof. Daniel Ferreira         */
/* Compilador: GCC (MinGW.org GCC-6.3.0-1) 6.3.0      */
/******************************************************/

#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdio.h>  // Necessário para o uso de FILE
#include "pgm.h"    // Para usar a estrutura "pgm"

#define LIMIAR 10   // Valor limite para considerar a homogeneidade de uma região

struct QuadTree {
    unsigned char valor; // Valor de intensidade da região, caso homogêneo
    int folha;           // 1 se for folha (homogêneo), 0 caso contrário
    struct QuadTree *nw, *ne, *sw, *se; // Filhos (noroeste, nordeste, sudoeste, sudeste)
};

// Funções de manipulação da Quadtree (compressão)

int homogeneo(struct pgm *, int, int, int, int);
struct QuadTree *comprimirQuadTree(struct pgm *, int, int, int, int);
void salvarCompressao(struct QuadTree *, FILE *);

// Funções de manipulação da Quadtree (descompressão)

struct QuadTree *carregarCompressao(FILE *);
void descomprimirQuadTree(struct QuadTree *, unsigned char *, int, int, int, int, int);

// Liberar memória alocada (compressão e descompressão)

void liberarQuadTree(struct QuadTree *);

#endif