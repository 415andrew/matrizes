all:matrizes	mimo

matrizes:matrizes.o	main.o
		gcc	-o	matrizes	matrizes.o	main.o	-I/usr/local/include/gsl	-I/home/gsl-2.7.1/gsl	-L/home/gsl-2.7.1/.libs	-L/home/gsl-2.7.1/cblas/.libs	-lgsl	-lgslcblas

matrizes.o:matrizes.c
		gcc	-o	matrizes.o	-c	matrizes.c	-W	-Wall	-pedantic

main.o:main.c	matrizes.h
	gcc	-o	main.o	-c	main.c -W -Wall	-pedantic

mimo: pds_telecom.c
	gcc	-o	mimo	pds_telecom.c	-I/usr/local/include/gsl	-I/home/gsl-2.7.1/gsl	-L/home/gsl-2.7.1/.libs	-L/home/gsl-2.7.1/cblas/.libs	-lgsl	-lgslcblas

clean:
	rm	-rf*.o
mrproper:clean
	rm	-rf	matrizes	mimo