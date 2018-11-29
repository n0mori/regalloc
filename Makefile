deps = Lista.o Hash.o Grafo.o Nick_string.o 

regalloc: $(deps) main.o
	gcc $(deps) main.c -o regalloc -lm

main.o: main.c
	gcc -c main.c

Lista.o: Lista.c
	gcc -c Lista.c

Hash.o: Hash.c
	gcc -c Hash.c

Grafo.o: Grafo.c
	gcc -c Grafo.c

Nick_string.o: Nick_string.c
	gcc -c Nick_string.c