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
    char numbers[10], other[10];

    for (int i = 0; i < regs; i++) {
        sprintf(numbers, "%d", i);

        Reg r = grafo_get_vertex_data(g, numbers);

        if (r == NULL) {
            r = new_reg(i, i, 1);
            grafo_insert_vertex(g, numbers, r);
        }

        for (int j = i; j < regs; j++) {
            sprintf(other, "%d", j);

            Reg r = grafo_get_vertex_data(g, other);

            if (r == NULL) {
                r = new_reg(j, j, 1);
                grafo_insert_vertex(g, other, r);
            }

            grafo_insert_edge(g, numbers, other, NULL);
            grafo_insert_edge(g, other, numbers, NULL);

            other[0] = 0;
        }

        numbers[0] = 0;
    }
    return g;
}

int barran = 0;

void prt() {
    if (!barran) {
        barran = 1;
    } else {
        printf("\n");
    }
}

void process_graph(Grafo g, int regs, int graphnum);

int main() {
    char buffer[10000];
    int gnum, regs, src, dest;
    int loaded = 0;
    Grafo g;

    for (;;) {
        char *token;

        fgets(buffer, 10000, stdin);

        token = strtok(buffer, " ");

        if (buffer[0] == 0) {
            
        } else if (!strcmp(token, "Graph")) {

            if (loaded) {
                process_graph(g, regs, gnum);
            }

            token = strtok(NULL, " ");
            sscanf(token, "%d:", &gnum);
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

    process_graph(g, regs, gnum);
}

int count_neighbours(Vertex v, Lista l) {
    Node n;
    int count = 0;

    for (n = get_first(l); n != NULL; n = get_next(l, n)) {
        Vertex v = get(l, n);
        Reg r = (Reg) vertex_get_data(v);

        if (r->active) {
            count++;
        }

    }

    return count;
}

int count_all(Grafo g) {
    Node n;
    Lista l = grafo_all_vertex(g);
    int count = 0;

    for (n = get_first(l); n != NULL; n = get_next(l, n)) {
        Vertex v = get(l, n);
        Reg r = (Reg) vertex_get_data(v);

        if (r->active) {
            count++;
        }

    }

    while (length_lista(l)) {
        remove_first(l);
    }
    free_lista(l);

    return count;
}

Vertex find_lonely(Grafo g, int regs) {
    Node n;
    Lista l = grafo_all_vertex(g);
    Vertex m = NULL;

    for (n = get_first(l); n != NULL; n = get_next(l, n)) {
        Vertex v = get(l, n);
        Reg r = (Reg) vertex_get_data(v);

        if (r->active) {
            Lista lx = create_lista();
            grafo_adjacentes(g, vertex_get_id(v), lx);
            int count = count_neighbours(v, lx);
            if (count <= regs) {
                while (length_lista(lx)) {
                    remove_first(lx);
                }
                m = v;
                return m;
            }
            while (length_lista(lx)) {
                remove_first(lx);
            }
            free_lista(lx);
        }
    }

    while (length_lista(l)) {
        remove_first(l);
    }
    free_lista(l);

    return m;
}

Vertex find_pot_spill(Grafo g, int regs) {
    Node n;
    Lista l = grafo_all_vertex(g);
    int maior = -1;
    Vertex m = NULL;

    for (n = get_first(l); n != NULL; n = get_next(l, n)) {
        Vertex v = get(l, n);
        Reg r = (Reg) vertex_get_data(v);

        if (r->active) {
            Lista lx = create_lista();
            grafo_adjacentes(g, vertex_get_id(v), lx);
            int count = count_neighbours(v, lx);

            if (count > maior) {
                maior = count;
                m = v;
            } else if (count == maior) {
                Reg big = vertex_get_data(m);
                if (big->id > r->id) {
                    m = v;
                }
            }

            while (length_lista(lx) > 0) {
                remove_first(lx);
            }
            free_lista(lx);
        }
    }

    while (length_lista(l)) {
        remove_first(l);
    }
    free_lista(l);

    return m;
}


Lista simplify(Grafo g, int regs, int graphnum) {
    Lista stack = create_lista();
    Vertex m;

    while (count_all(g)) {
        m = find_lonely(g, regs);

        if (m == NULL) {
            m = find_pot_spill(g, regs);
        }

        Reg r = vertex_get_data(m);
        r->active = 0;

        insert_first(stack, m);
    }

    return stack;

}

void assign(Grafo g, int regs, int graphnum, Lista stack) {
    int colors[regs];
    Reg r;
    Vertex v;
    Lista vizinhos = create_lista();

    while (length_lista(stack)) {
        v = remove_first(stack);
        r = vertex_get_data(v);

        grafo_adjacentes(g, vertex_get_id(v), vizinhos);

        for (int i = 0; i < regs; i++) {
            colors[i] = 0;
        }

        while (length_lista(vizinhos)) {
            Vertex viz = remove_first(vizinhos);
            Reg rz = vertex_get_data(viz);

            if (rz->active) {
                if (rz->color != -1) {
                    colors[rz->color] = 1;
                }
            }
        }

        if (r->id >= regs) {
            int full = 1;
            int c;

            for (c = 0; c < regs; c++) {
                if (!colors[c]) {
                    full = 0;
                    break;
                }
            }

            if (!full) {
                r->color = c;
                r->active = 1;
            } else {
                prt();
                printf("Graph %d: SPILL\n", graphnum);
                return;
            }
        } else {
            if (!colors[r->color]) {
                r->active = 1;
            } else {
                prt();
                printf("Graph %d: SPILL\n", graphnum);
                return;
            }
        }

    }

    prt();
    printf("Graph %d: SUCCESS\n", graphnum);
}

void process_graph(Grafo g, int regs, int graphnum) {
    Lista stk = simplify(g, regs, graphnum);

    assign(g, regs, graphnum, stk);

    Lista vertex = grafo_all_vertex(g);
    Lista edges = grafo_all_edges(g);

    while (length_lista(vertex)) {
        Vertex v = remove_first(vertex);
        free(vertex_get_data(v));
        free(v);
    }
    free_lista(vertex);

    while (length_lista(edges)) {
        Edge e = remove_first(edges);
        grafo_remove_edge(g, edge_get_from(e), edge_get_to(e));
    }
    free_lista(edges);

    grafo_free(g);
}