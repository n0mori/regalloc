#ifndef GRAFO__H
#define GRAFO__H

/* Um grafo é uma estrutura de dados que possui um conjunto de pontos finito e não-vazio
e um conjunto finito de arestas, que ligam esses pontos. Grafos são uteis em várias coisas,
como encontrar caminhos e rotas. 

|---------------------|
|        Grafo        |
|---------------------|
|   vertices : Hash   |
|   edges    : Hash   |
|---------------------|

|---------------------|
|       Vertex        |
|---------------------|
|     id  : string    |
|    data : void*     |
|---------------------|

|---------------------|
|        Edge         |
|---------------------|
|     id1 : string    |
|     id2 : string    |
|    data : void*     |
|---------------------|

*/

#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "Lista.h"
#include "Nick_string.h"

typedef void* Grafo;
typedef void* Edge;
typedef void* Vertex;

Grafo new_grafo();
void grafo_insert_vertex(Grafo g, char *id, void *data);
void *grafo_get_vertex_data(Grafo g, char *id);
void grafo_insert_edge(Grafo g, char *from, char *to, void *data);
void *grafo_get_edge_data(Grafo g, char *from, char *to);
void *grafo_remove_edge(Grafo g, char *from, char *to);
int  grafo_adjacente(Grafo g, char *from, char *to);
void grafo_adjacentes(Grafo g, char *id, Lista l);
void *edge_get_data(Edge e);
char *edge_get_from(Edge e);
char *edge_get_to(Edge e);
void *vertex_get_data(Vertex v);
char *vertex_get_id(Vertex v);
Lista grafo_all_vertex(Grafo g);
Lista grafo_all_edges(Grafo g);
void grafo_free(Grafo g);

#endif