# Targets
all: compressor descompressor

# Executáveis
compressor: source/compressor.o source/pgm.o source/quadtree.o
	gcc -o compressor source/compressor.o source/pgm.o source/quadtree.o

descompressor: source/descompressor.o source/pgm.o source/quadtree.o
	gcc -o descompressor source/descompressor.o source/pgm.o source/quadtree.o

# Compilação dos arquivos objeto
source/compressor.o: source/compressor.c source/pgm.h source/quadtree.h
	gcc -c source/compressor.c -o source/compressor.o

source/descompressor.o: source/descompressor.c source/pgm.h source/quadtree.h
	gcc -c source/descompressor.c -o source/descompressor.o

source/pgm.o: source/pgm.c source/pgm.h
	gcc -c source/pgm.c -o source/pgm.o

source/quadtree.o: source/quadtree.c source/quadtree.h
	gcc -c source/quadtree.c -o source/quadtree.o

# Limpeza
clean:
	rm -rf source/*.o compressor descompressor