GCC = gcc
FLAGS = -c

PROGRAMAS: labmodular

labmodular: 
	$(GCC) $(FLAGS) librerialab.c
	$(GCC) $@.c librerialab.o -o $@
	$(RM) *.o
	
clear:
	$(RM) *.o $(PROGRAMAS)