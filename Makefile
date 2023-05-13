all:matrizes

matrizes:matrizes.o	main.o
		gcc	-o	matrizes	matrizes.o	main.o

matrizes.o:matrizes.c
		gcc	-o	matrizes.o	-c	matrizes.c	-W	-Wall	-pedantic

main.o:main.c	matrizes.h
	gcc	-o	main.o	-c	main.c -W -Wall	-pedantic

clean:
	rm	-rf*.o
mrproper:clean
	rm	-rf	matrizes