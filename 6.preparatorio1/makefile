# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g -Werror -Wextra  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = testa_lista.o liblista_ordenada.o 

all: testa_lista.o liblista_ordenada.o
	$(CC) -o testa_lista testa_lista.o liblista_ordenada.o $(LDFLAGS)

liblista_ordenada.o: liblista_ordenada.c
	$(CC) -c $(CFLAGS) liblista_ordenada.c

testa_lista.o: testa_lista.c
	$(CC) -c $(CFLAGS) testa_lista.c

clean:
	rm -f $(objects) testa_lista