deps = Lista.o Hash.o Grafo.o Nick_string.o 

regalloc: $(deps) main.o
	gcc -g $(deps) main.c -o regalloc -lm

main.o: main.c
	gcc -g -c main.c

Lista.o: Lista.c
	gcc -g -c Lista.c

Hash.o: Hash.c
	gcc -g -c Hash.c

Grafo.o: Grafo.c
	gcc -g -c Grafo.c

Nick_string.o: Nick_string.c
	gcc -g -c Nick_string.c