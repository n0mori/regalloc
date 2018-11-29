#ifndef LISTA__H
#define LISTA__H

/*
Uma lista é uma coleção de objetos.
*/

typedef void* Lista;
typedef void* Node;

#include <stdlib.h>
#include <stdio.h>

Lista create_lista();
int length_lista(Lista lista);
int insert_first(Lista lista, void *val);
int insert_last(Lista lista, void *val);
int insert_after(Lista lista, Node posic, void *val);
int insert_before(Lista lista, Node posic, void *val);
void *remove_first(Lista lista);
void *remove_last(Lista lista);
void *remove_at(Lista lista, Node posic);
Node get_first(Lista lista);
Node get_last(Lista lista);
Node get_next(Lista lista, Node posic);
Node get_before(Lista lista, Node posic);
void *get(Lista lista, Node posic);
void free_lista(Lista lista);
void *search_lista(Lista lista, int (*compar)(void* a, void *b), void *comparado);
void *seek_and_destroy_lista(Lista lista, int (*compar)(void* a, void *b), void *comparado);

#endif
