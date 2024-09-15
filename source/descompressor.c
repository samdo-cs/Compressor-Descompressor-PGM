/******************************************************/
/* Aluno: Gabriel ícaro Barbosa Rocha                 */
/* Matricula: 20232045050155                          */
/* Aluno: Isaac de Brito Azevedo                      */
/* Matricula: 20232045050520                          */
/* Avaliacão 04: Trabalho Final                       */
/* 04.505.23 – 2024.1 – Prof. Daniel Ferreira         */
/* Compilador: GCC (MinGW.org GCC-6.3.0-1) 6.3.0      */
/******************************************************/

#include "pgm.h"
#include "quadtree.h"
#include <stdio.h>
#include <stdlib.h>

// Função principal
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Formato: \n\t%s <imagemEntrada.bin> <imagemSaida.pgm>\n", argv[0]);
        exit(1);
    }

    struct pgm img;
    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        perror("Erro ao abrir arquivo de entrada.");
        exit(1);
    }

    // Ler o cabeçalho da imagem comprimida
    lerCabecalho(&img, in);

    // Carregar a Quadtree comprimida
    struct QuadTree *root = carregarCompressao(in);
    fclose(in);

    // Alocar espaço para a imagem descomprimida
    img.pData = (unsigned char *)malloc(img.r * img.c * sizeof(unsigned char));
    if (!img.pData) {
        perror("Erro ao alocar memória para a imagem descomprimida.");
        exit(1);
    }

    // Descomprimir a Quadtree para a imagem
    descomprimirQuadTree(root, img.pData, 0, 0, img.c, img.r, img.c);

    // Escrever a imagem PGM descomprimida
    escreverImagemPGM(&img, argv[2]);

    // Liberar memória
    liberarQuadTree(root);
    free(img.pData);

    return 0;
}