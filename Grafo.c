#include "Grafo.h"

typedef struct vertex {
  char id[20];
  void *data;
}* StVertex;

typedef struct edge {
  char from[20];
  char to[20];
  void *data;
}* StEdge;

typedef struct grafo {
  Hash vertices;
  Hash edges;
}* StGrafo;

int cmpt(void *a, void *b) {
  return 1;
}

Grafo new_grafo() {
  StGrafo g = malloc(sizeof(struct grafo));
  g->vertices = new_hash(1);
  g->edges = new_hash(1);
  return g;
}

StVertex new_vertex(char *id, void *data) {
  StVertex v = malloc(sizeof(struct vertex));
  strcpy(v->id, id);
  v->data = data;
  return v; 
}

void grafo_insert_vertex(Grafo g, char *id, void *data) {
  StGrafo grafo = (StGrafo) g;
  StVertex v = new_vertex(id, data);
  hash_insert(grafo->vertices, id, v);
}

void *grafo_get_vertex_data(Grafo g, char *id) {
  StGrafo grafo = (StGrafo) g;
  StVertex v = hash_get(grafo->vertices, id);
  if (v == NULL) {
    return NULL;
  }
  return v->data;
}

char *edge_join(char *from, char *to) {
  char *s = alloc_inicial();
  s = concatena(s, from);
  s = concatena(s, " ");
  s = concatena(s, to);
  return s;
}

StEdge new_edge(char *from, char *to, void *data) {
  StEdge e = malloc(sizeof(struct edge));
  strcpy(e->from, from);
  strcpy(e->to, to);
  e->data = data;
  return e;
}

int cmp_edge_edge(void *a, void *b) {
  StEdge ea = (StEdge) a;
  StEdge eb = (StEdge) b;

  return (strcmp(ea->from, eb->from) == 0 && strcmp(ea->to, eb->to) == 0);
}

int cmp_edge_from(void *id, void *edge) {
  StEdge e = (StEdge) edge;
  return strcmp(id, e->from) == 0;
}

void *free_edge(StEdge e) {
  void *data = e->data;
  free(e);
  return data;
}

void grafo_insert_edge(Grafo g, char *from, char *to, void *data) {
  StGrafo grafo = (StGrafo) g;
  StEdge e;
  StVertex vfrom, vto;
  char *key;

  vfrom = hash_get(grafo->vertices, from);
  vto = hash_get(grafo->vertices, to);

  if (vfrom == NULL || vto == NULL) {
    return;
  }

  e = new_edge(from, to, data);
  
  key = edge_join(from, to);
  hash_insert(grafo->edges, key, e);
  free(key);

}

void *grafo_get_edge_data(Grafo g, char *from, char *to) {
  StGrafo grafo = (StGrafo) g;
  StEdge e;
  char *key;

  key = edge_join(from, to);

  e = hash_get(grafo->edges, key);

  free(key);

  if (e == NULL) {
    return NULL;
  }

  return e->data;
}

void *grafo_remove_edge(Grafo g, char *from, char *to) {
  void *data;
  StGrafo grafo = (StGrafo) g;
  StEdge e;
  char *key;

  key = edge_join(from, to);

  e = hash_delete(grafo->edges, key);
  free(key);

  if (e == NULL) {
    return NULL;
  }

  data = free_edge(e);
  return data;
  
}

int grafo_adjacente(Grafo g, char *from, char *to) {
  StGrafo grafo = (StGrafo) g;
  StEdge e;
  char *key;

  key = edge_join(from, to);

  e = hash_get(grafo->edges, key);

  free(key);

  if (e == NULL) {
    return 0;
  }

  return 1;
    
}

void grafo_adjacentes(Grafo g, char *id, Lista l) {
  StGrafo grafo = (StGrafo) g;
  Lista edges = create_lista();

  hash_filter(grafo->edges, edges, cmp_edge_from, id);

  while (length_lista(edges) > 0) {
    StEdge e = (StEdge) remove_first(edges);
    Vertex v = hash_get(grafo->vertices, e->to);
    insert_last(l, v);
  }
  free(edges);

}

void *edge_get_data(Edge e) {
  StEdge edge = (StEdge) e;
  return edge->data;
}

void *vertex_get_data(Vertex v) {
  StVertex vertex = (StVertex) v;
  return vertex->data;
}

char *vertex_get_id(Vertex v) {
  StVertex vertex = (StVertex) v;
  return vertex->id;
}

Lista grafo_all_vertex(Grafo g) {
  Lista list = create_lista();
  StGrafo grafo = (StGrafo) g;
  hash_filter(grafo->vertices, list, cmpt, NULL);
  return list;
}

Lista grafo_all_edges(Grafo g) {
  Lista list = create_lista();
  StGrafo grafo = (StGrafo) g;
  hash_filter(grafo->edges, list, cmpt, NULL);
  return list;
}

char *edge_get_from(Edge e) {
  StEdge edge = (StEdge) e;

  return edge->from;
}

char *edge_get_to(Edge e) {
  StEdge edge = (StEdge) e;

  return edge->to;
}

void donone(void *a) {

}

void grafo_free(Grafo g) {
  StGrafo grafo = (StGrafo) g;

  hash_delete_all(grafo->edges);
  hash_delete_all(grafo->vertices);

  free(g);
}