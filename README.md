# Compressor e Descompressor de Imagens do tipo PGM em C

Este projeto implementa em C, a compressão e descompressão de imagens no formato PGM (Portable GrayMap).

## Funcionamento Geral

O projeto é dividido em dois programas principais: **compressor** e **descompressor**.

### Compressor

* Reduz o tamanho das imagens PGM usando um algoritmo baseado em quadtree.
* **Funcionamento**:
  * Lê a imagem PGM.
  * Constrói a quadtree da imagem.
  * Gera um bitstream a partir da quadtree.
  * Salva o bitstream em um arquivo.

### Descompressor

* Reconstrói a imagem PGM original a partir do arquivo comprimido.
* **Funcionamento**:
  * Lê o bitstream do arquivo.
  * Reconstrói a quadtree a partir do bitstream.
  * Converte a quadtree de volta em uma imagem PGM.
  * Salva a imagem descomprimida.

### Quadtree

*   Estrutura de dados usada para dividir a imagem em quadrantes menores, facilitando a compressão.
* **Funcionamento**:
  * Cada quadrante é subdividido até que todos os pixels em um quadrante sejam uniformes ou até um tamanho mínimo ser alcançado.

### Bitstream

*   Sequência de bits que representa a imagem comprimida.
* **Funcionamento**:
  * Durante a compressão, a imagem é convertida em uma sequência de bits que é armazenada em um arquivo.
  * Durante a descompressão, essa sequência de bits é lida e convertida de volta para a imagem original.

## Compilação e Execução

1. **Compilação**: Execute o `Makefile` para compilar o projeto. No diretório do projeto, execute:
  ```
  make
  ```
Isso gerará os executáveis `compressor` e `descompressor`.

2. **Execução**:
- Para compressão:
  ```
  ./compressor <entrada.pgm> <saida.bin>
  ```
- Para descompressão:
  ```
  ./descompressor <entrada.bin> <saida.pgm>
  ```

O arquivo de entrada deve estar no mesmo diretório onde os executáveis `compressor` e `descompressor` são executados.

## Integrantes

- **Gabriel ícaro Barbosa Rocha**
- **Isaac de Brito Azevedo**
