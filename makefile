# MAKEFILE
#gcc -g -o exect *.c

# Nome do compilador
CC = gcc

# Wildcards eh utilizado para listar os arquivos fonte no diretorio atual
FONTES = $(wildcard *.c)

# Gera a lista dos arquivos objeto usando a lista de arquivo fonte
OBJETOS = $(FONTES: .c=.o)

# Nome do arquivo executavel
EXECUTAVEL = trab2

# all: prog
all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(CC) -g -o $@ $^ 

%.o: %.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm $(EXECUTAVEL)

rmproper: clean
	rm -rf $(EXECUTAVEL)

run: $(EXECUTAVEL)
	./$(EXECUTAVEL) exemplos/N10_S3_C3_M3.txt mysolutions/N10_S3_C3_M3-solution.txt
valgrind: $(EXECUTAVEL)
	valgrind ./$(EXECUTAVEL) exemplos/N10000_S50_C300_M10.txt mysolutions/N10000_S50_C300_M10-solution.txt