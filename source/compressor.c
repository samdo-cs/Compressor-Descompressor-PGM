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
    struct pgm img;

    // Verifica se o número correto de argumentos foi passado
    if (argc != 3) {
        printf("Formato: \n\t%s <imagemEntrada.pgm> <imagemSaida.bin>\n", argv[0]);
        exit(1);
    }

    // Lê a imagem PGM
    lerPGM(&img, argv[1]);

    // Comprimir a imagem usando Quadtree
    struct QuadTree *raiz = comprimirQuadTree(&img, 0, 0, img.r, img.c);

    // Abre o arquivo para salvar a compressão
    FILE *out = fopen(argv[2], "wb");
    if (!out) {
        perror("Erro ao abrir arquivo de saída.");
        exit(1);
    }

    // Salva o cabeçalho da imagem PGM no arquivo
    salvarCabecalho(&img, out);

    // Salva a árvore comprimida no arquivo binário
    salvarCompressao(raiz, out);
    
    // Fecha o arquivo
    fclose(out);

    // Liberar a memória alocada
    liberarQuadTree(raiz);
    free(img.pData);

    return 0;
}