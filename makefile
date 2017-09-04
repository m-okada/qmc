all : qmc mask12.h
.PHONY : all

mask12.h : mask12.c
	gcc mask12.c -o mask12
	./mask12 > mask12.h

qmc : qmc_main.c qmc.h qmc_misc.c qmc_misc.h readfile.c readfile.h mask12.h
	gcc qmc_main.c qmc_misc.c readfile.c -o qmc -Wall -O3 -std=c99

