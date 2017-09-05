cl mask12.c
mask12 > mask12.h
cl qmc_main.c qmc_misc.c readfile.c /Feqmc.exe /Ox
del *.obj