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
#include <stdio.h>
#include <stdlib.h>

// Função para ler a imagem PGM
void lerPGM(struct pgm *pio, char *filename) {
    FILE *fp;
    char ch;

    // Abre o PGM de acordo com o sistema operacional
    #ifdef _WIN32
        if (!(fp = fopen(filename, "rb"))) { // Windows usa modo binário "rb"
            perror("Erro.");
            exit(1);
        }

    #else
        if (!(fp = fopen(filename, "r"))) { // Linux/Unix usa modo texto "r"
        perror("Erro.");
        exit(1);
        }
    #endif

    if ((ch = getc(fp)) != 'P') {
        puts("A imagem fornecida não está no formato PGM");
        exit(2);
    }

    pio->tipo = getc(fp) - 48;
    fseek(fp, 1, SEEK_CUR);

    while ((ch = getc(fp)) == '#') {
        while ((ch = getc(fp)) != '\n');
    }

    fseek(fp, -1, SEEK_CUR);

    fscanf(fp, "%d %d", &pio->c, &pio->r);
    if (ferror(fp)) {
        perror(NULL);
        exit(3);
    }
    fscanf(fp, "%d", &pio->mv);
    fseek(fp, 1, SEEK_CUR);

    pio->pData = (unsigned char *)malloc(pio->r * pio->c * sizeof(unsigned char));

    switch (pio->tipo) {
    case 2:
        for (int k = 0; k < (pio->r * pio->c); k++) {
        
        #ifdef _WIN32
            // Windows usa %u (unsigned int) e temos que converter para unsigned char
            unsigned int temp;
            fscanf(fp, "%u", &temp);
            pio->pData[k] = (unsigned char)temp;
        #else
            // Linux/Unix usa %hhu diretamente
            fscanf(fp, "%hhu", pio->pData + k);
        #endif

        }
        break;
    case 5:
        fread(pio->pData, sizeof(unsigned char), pio->r * pio->c, fp);
        break;
    default:
        puts("Não está implementado");
    }

    fclose(fp);
}

// Função para gravar o cabeçalho PGM 
void salvarCabecalho(struct pgm *img, FILE *out) {

    // Gravar informações básicas do PGM
    char tipo[2] = {'P', '5'};   // Tipo PGM (binário)
    fwrite(tipo, sizeof(char), 2, out);  // Gravar "P5"
    
    // Gravar dimensões (largura e altura)
    fwrite(&img->c, sizeof(int), 1, out); // Gravar largura (colunas)
    fwrite(&img->r, sizeof(int), 1, out); // Gravar altura (linhas)
    fwrite(&img->mv, sizeof(unsigned char), 1, out); // Gravar valor máximo de intensidade
}

// Função para ler o cabeçalho da imagem PGM do arquivo comprimido
void lerCabecalho(struct pgm *img, FILE* inFile) {
    char tipo[2];
    fread(tipo, sizeof(char), 2, inFile);  // Ler "P5"
    if (tipo[0] != 'P' || tipo[1] != '5') {
        printf("Arquivo não está no formato PGM binário.\n");
        exit(1);
    }

    // Ler largura, altura e valor máximo de intensidade
    fread(&img->c, sizeof(int), 1, inFile);  // Largura
    fread(&img->r, sizeof(int), 1, inFile);  // Altura
    unsigned char mv;
    fread(&mv, sizeof(unsigned char), 1, inFile);  // Valor máximo
    img->mv = mv;
}

// Função para escrever a imagem descomprimida no formato PGM
void escreverImagemPGM(struct pgm *img, char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Erro ao abrir arquivo de saída.");
        exit(1);
    }

    fprintf(fp, "P5\n");
    fprintf(fp, "%d %d\n", img->c, img->r);
    fprintf(fp, "%d\n", img->mv);

    fwrite(img->pData, sizeof(unsigned char), img->r * img->c, fp);
    fclose(fp);
}