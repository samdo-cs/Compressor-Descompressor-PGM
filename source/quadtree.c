/******************************************************/
/* Aluno: Gabriel ícaro Barbosa Rocha                 */
/* Matricula: 20232045050155                          */
/* Aluno: Isaac de Brito Azevedo                      */
/* Matricula: 20232045050520                          */
/* Avaliacão 04: Trabalho Final                       */
/* 04.505.23 – 2024.1 – Prof. Daniel Ferreira         */
/* Compilador: GCC (MinGW.org GCC-6.3.0-1) 6.3.0      */
/******************************************************/

#include "quadtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Compressão
// Função que verifica se uma região da imagem é homogênea
int homogeneo(struct pgm *img, int startX, int startY, int endX, int endY) {
    unsigned char firstValue = img->pData[startY * img->c + startX];
    int sum = 0, count = 0;
    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            unsigned char pixel = img->pData[y * img->c + x];
            sum += abs(pixel - firstValue);
            count++;
            if (sum / count >= LIMIAR) {
                return 0; // Não homogêneo
            }
        }
    }
    return 1; // Homogêneo
}

// Função que comprime a imagem utilizando Quadtree
struct QuadTree *comprimirQuadTree(struct pgm *img, int startX, int startY, int endX, int endY) {
    struct QuadTree *node = (struct QuadTree *)malloc(sizeof(struct QuadTree));

    if (homogeneo(img, startX, startY, endX, endY)) {
        node->folha = 1;
        node->valor = img->pData[startY * img->c + startX]; // Todos os pixels têm o mesmo valor
        node->nw = node->ne = node->sw = node->se = NULL;
    } else {
        node->folha = 0;
        int midX = (startX + endX) / 2;
        int midY = (startY + endY) / 2;

        // Dividir em quatro quadrantes
        node->nw = comprimirQuadTree(img, startX, startY, midX, midY);
        node->ne = comprimirQuadTree(img, midX, startY, endX, midY);
        node->sw = comprimirQuadTree(img, startX, midY, midX, endY);
        node->se = comprimirQuadTree(img, midX, midY, endX, endY);
    }

    return node;
}

// Função para salvar a árvore comprimida em um arquivo binário
void salvarCompressao(struct QuadTree *node, FILE *out) {
    if (node->folha) {
        fputc(1, out); // Indica que é um nó folha
        fputc(node->valor, out); // Grava o valor do pixel
    } else {
        fputc(0, out); // Indica que é um nó interno
        salvarCompressao(node->nw, out);
        salvarCompressao(node->ne, out);
        salvarCompressao(node->sw, out);
        salvarCompressao(node->se, out);
    }
}

// Descompressão
// Função para carregar a Quadtree comprimida de um arquivo binário
struct QuadTree *carregarCompressao(FILE *in) {
    struct QuadTree *node = (struct QuadTree *)malloc(sizeof(struct QuadTree));
    if (!node) {
        perror("Erro ao alocar memória para a Quadtree");
        exit(1);
    }

    int tipo = fgetc(in);

    if (tipo == 1) {
        // Nó folha
        node->folha = 1;
        node->valor = fgetc(in);
        node->nw = node->ne = node->sw = node->se = NULL;
    } else {
        // Nó interno
        node->folha = 0;
        node->nw = carregarCompressao(in);
        node->ne = carregarCompressao(in);
        node->sw = carregarCompressao(in);
        node->se = carregarCompressao(in);
    }

    return node;
}

// Função para descomprimir a Quadtree e reconstruir a imagem
void descomprimirQuadTree(struct QuadTree *node, unsigned char *pData, int startX, int startY, int endX, int endY, int larguraTotal) {
    if (node->folha) {
        // Preencher a região com o valor do nó folha
        for (int y = startY; y < endY; y++) {
            for (int x = startX; x < endX; x++) {
                pData[y * larguraTotal + x] = node->valor;
            }
        }
    } else {
        // Dividir a região em quatro quadrantes e descomprimir cada um
        int midX = (startX + endX) / 2;
        int midY = (startY + endY) / 2;

        descomprimirQuadTree(node->nw, pData, startX, startY, midX, midY, larguraTotal);
        descomprimirQuadTree(node->ne, pData, midX, startY, endX, midY, larguraTotal);
        descomprimirQuadTree(node->sw, pData, startX, midY, midX, endY, larguraTotal);
        descomprimirQuadTree(node->se, pData, midX, midY, endX, endY, larguraTotal);
    }
}

// Compressão e Descompressão
// Função que libera a memória da Quadtree
void liberarQuadTree(struct QuadTree *node) {
    if (!node) return;
    if (!node->folha) {
        liberarQuadTree(node->nw);
        liberarQuadTree(node->ne);
        liberarQuadTree(node->sw);
        liberarQuadTree(node->se);
    }
    free(node);
}