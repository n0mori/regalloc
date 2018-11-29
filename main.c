#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "Lista.h"
#include "Grafo.h"

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int find_less(char *str) {
    int i = 0;
    for (;;) {
        if (str[i] == '<') {
            return 1;
        } else if (str[i] == 0) {
            return 0;
        }
        i++;
    }

}

Grafo initialize_graph(int regs) {
    Grafo g = new_grafo();
    char numbers[100];

    for (int i = 0; i < regs; i++) {
        sprintf(numbers, "%d", i);
        grafo_insert_vertex(g, numbers, i);
    }
    return g;
}

int main() {
    char buffer[10000];
    int gnum, regs, src, dest;
    int loaded = 0;
    Grafo g;

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
            //printf("Graph %d\n", gnum);
            loaded = 1;
        } else if (token[0] == 'K') {
            sscanf(token, "K=%d", &regs);

            g = initialize_graph(regs);

        } else if (isDigit(token[0]) && !find_less(token)) {
            char *str_src = alloc_inicial();
            str_src = concatena(str_src, token);

            sscanf(token, "%d", &src);

            grafo_insert_vertex(g, str_src, -1);

            token = strtok(NULL, " ");
            token = strtok(NULL, " ");

            while (token != NULL) {
                int dest;
                
                sscanf(token, "%d", &dest);

                grafo_insert_edge(g, str_src, token, -1);

                token = strtok(NULL, " ");

            }
            
        } else if (isDigit(token[0]) && find_less(token)) {

        } else {
        }


        if (feof(stdin)) {
            break;
        }

        buffer[0] = 0;
    }

    //execute the last one
}