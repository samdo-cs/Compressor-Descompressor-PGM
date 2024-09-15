# Compressor e Descompressor de Imagens do tipo PGM em C

Este projeto implementa em C, a compressão e descompressão de imagens no formato PGM (Portable GrayMap). O projeto inclui dois executáveis: `compressor` e `descompressor`. 

## Compilação e Execução

1. **Compilação**: Execute o `Makefile` para compilar o projeto. No diretório do projeto, execute:
  ```
  make
  ```
Isso gerará os executáveis `compressor` e `descompressor`.

2. **Execução**:
- Para compressão:
  ```
  ./compressor <entrada.pgm> <saida.pgm>
  ```
- Para descompressão:
  ```
  ./descompressor <entrada.pgm> <saida.pgm>
  ```

O arquivo de entrada deve estar no mesmo diretório onde os executáveis `compressor` e `descompressor` são executados.
Certifique-se de substituir `<entrada.pgm>` e `<saida.pgm>` pelos caminhos reais dos arquivos de imagem PGM que você deseja processar.

## Integrantes

- **Gabriel ícaro Barbosa Rocha**
- **Isaac de Brito Azevedo**
