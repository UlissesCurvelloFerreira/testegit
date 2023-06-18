# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g -Werror -Wextra  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = testa_lista.o liblista_circular.o 

all: testa_lista.o liblista_circular.o
	$(CC) -o testa_lista testa_lista.o liblista_circular.o $(LDFLAGS)

liblista_circular.o: liblista_circular.c
	$(CC) -c $(CFLAGS) liblista_circular.c

testa_lista.o: testa_lista.c
	$(CC) -c $(CFLAGS) testa_lista.c

clean:
	rm -f $(objects) testa_lista