#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "Lista.h"
#include "Grafo.h"

typedef struct st_g {
    int id;
    int color;
    int active;
}* Reg;

Reg new_reg(int id, int color, int active) {
    Reg r = malloc(sizeof(struct st_g));
    r->id = id;
    r->color = color;
    r->active = active;
    return r;
}

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

        Reg r = new_reg(i, i, 1);

        grafo_insert_vertex(g, numbers, r);
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

            Reg r = grafo_get_vertex_data(g, str_src);

            if (r == NULL) {
                r = new_reg(src, -1, 1);
                grafo_insert_vertex(g, str_src, r);
            }

            token = strtok(NULL, " ");
            token = strtok(NULL, " ");

            while (token != NULL) {
                int dest;
                
                sscanf(token, "%d", &dest);

                Reg r1 = grafo_get_vertex_data(g, str_src);

                if (r1 == NULL) {
                    r1 = new_reg(dest, -1, 1);
                    grafo_insert_vertex(g, str_src, r);
                }

                grafo_insert_edge(g, str_src, token, NULL);

                token = strtok(NULL, " ");

            }
        }


        if (feof(stdin)) {
            break;
        }

        buffer[0] = 0;
    }

    //execute the last one
}