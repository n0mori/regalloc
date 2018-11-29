#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "Lista.h"
#include "Grafo.h"

Grafo initialize_graph(int regs) {
    Grafo g = new_grafo();
    char numbers[100];

    for (int i = 0; i < regs; i++) {
        sprintf(numbers, "%d", i);
        grafo_insert_vertex(g, numbers, i);
    }
}

int main() {
    char buffer[10000];
    int gnum, regs;
    int loaded = 0;

    for (;;) {
        char *token;

        fgets(buffer, 10000, stdin);

        token = strtok(buffer, " ");

        if (!strcmp(token, "Graph")) {

            if (loaded) {
                //execute coloring
            }

            token = strtok(NULL, " ");
            sscanf(token, "%d:", &gnum);
            printf("Graph %d\n", gnum);
            loaded = 1;
        } else if (token[0] == 'K') {
            sscanf(token, "K=%d", &regs);

            Grafo g = initialize_graph(regs);

            printf("%d\n", grafo_get_vertex_data(g, "3"));

        } else {
            return 0;
        }


        if (feof(stdin)) {
            break;
        }

        buffer[0] = 0;
    }

    //execute the last one
}