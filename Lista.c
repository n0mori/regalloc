#include "Lista.h"

typedef struct node {
  struct node *prev;
  void *val;
  struct node *next;
}* StNode;

typedef struct lista {
  StNode head;
  StNode tail;
  int length;
}* StLista;

Lista create_lista() {
  Lista l = malloc(sizeof(struct lista));
  StLista lista = (StLista) l;
  lista->head = NULL;
  lista->tail = NULL;
  lista->length = 0;
  return l;
}

int length_lista(Lista lista) {
  /*if (l.head == NULL || l.tail == NULL) {
    return 0;
  }
  Node *n;
  i = 0;
  for (n = head; n->next != NULL; n = n->next) {
    i++;
  }
  return i;*/
  StLista l = (StLista) lista;
  return l->length;
}

int insert_first(Lista lista, void *val) {
  Node node = malloc(sizeof(struct node));
  StNode n = (StNode) node;
  StLista l = (StLista) lista;
  n->prev = NULL;
  n->val = val;
  n->next = l->head;
  l->head = n;
  l->length++;
  if (n->next != NULL) {
    n->next->prev = l->head;
  }
  if (l->tail == NULL) {
    l->tail = l->head;
  }
  return 1;
}

int insert_last(Lista lista, void *val) {
  Node node;
  StNode n;
  StLista l = (StLista) lista;

  if (length_lista(l) == 0) {
    insert_first(l, val);
    return 1;
  }
  
  node = malloc(sizeof(struct node));
  n = (StNode) node;

  n->prev = l->tail;
  n->prev->next = n;
  n->val = val;
  n->next = NULL;
  l->tail = n;
  l->length++;
  if (l->head == NULL) {
    l->head = l->tail;
  }
  return 1;
}

int insert_before(Lista lista, Node posic, void *val) {
  Node n;
  StNode new, pos;
  StLista l = (StLista) lista;

  if (posic == l->head) {
    insert_first(l, val);
    return 1;
  }

  n = malloc(sizeof(struct node));
  new = (StNode) n;
  pos = (StNode) posic;

  new->prev = pos->prev;
  new->prev->next = new;
  new->val = val;
  new->next = pos;
  pos->prev = new;
  l->length++;
  return 1;
}

int insert_after(Lista lista, Node posic, void *val) {
  Node n;
  StNode new, pos;
  StLista l = (StLista) lista;

  if (posic == l->tail) {
    insert_last(l, val);
    return 1;
  }

  n = malloc(sizeof(struct node));
  new = (StNode) n;
  pos = (StNode) posic;

  new->next = pos->next;
  pos->next = new;
  new->val = val;
  new->prev = pos;
  new->next->prev = new;
  l->length++;
  return 1;
}

void *remove_first(Lista lista) {
  StNode aux;
  StLista l = (StLista) lista;
  void *p;
  p = l->head->val;

  if (l->head == NULL) {
    return NULL;
  }
  if (l->head == l->tail) {
    free(l->head);
    l->head = NULL;
    l->tail = NULL;
    l->length--;
    return p;
  }

  aux = l->head;
  l->head = aux->next;
  l->head->prev = NULL;
  l->length--;
  free(aux);
  return p;
}

void *remove_last(Lista lista) {
  StNode aux;
  StLista l = (StLista) lista;
  void *p = l->tail->val;

  if (l->length == 0 || l->tail == NULL) {
    return NULL;
  }
  if (l->head == l->tail) {
    free(l->head);
    l->head = NULL;
    l->tail = NULL;
    l->length--;
    return p;
  }

  aux = l->tail;
  l->tail = aux->prev;
  l->tail->next = NULL;
  l->length--;
  free(aux);
  return p;
}

void *remove_at(Lista lista, Node posic) {
  StNode pos = (StNode) posic;
  StLista l = (StLista) lista;
  void *p = pos->val;

  if (pos == l->head) {
    p = remove_first(l);
    return p;
  }
  if (pos == l->tail) {
    p = remove_last(l);
    return p;
  }

  pos->prev->next = pos->next;
  pos->next->prev = pos->prev;
  l->length--;
  free(pos);
  return p;
}

Node get_first(Lista lista) {
  StLista l = (StLista) lista;
  return l->head;
}

Node get_last(Lista lista) {
  StLista l = (StLista) lista;
  return l->tail;
}

Node get_next(Lista lista, Node posic) {
  StNode pos = (StNode) posic;
  return pos->next;
}

Node get_before(Lista lista, Node posic) {
  StNode pos = (StNode) posic;
  return pos->prev;
}

void *get(Lista lista, Node posic) {
  StNode pos = (StNode) posic;
  return pos->val;
}

void free_lista(Lista lista) {
  /*Node *aux;
  if (l->head == NULL || l->tail == NULL) {
    return;
  }
  for (aux = l->head; aux->next != NULL; aux = aux->next) {
    if (aux->prev != NULL) {
      free(aux->prev);
    }
  }
  free(l->tail);
  */

  StLista l = (StLista) lista;
  for (; l->length > 0;) {
    void *val = remove_first(l);
    if (val != NULL) {
      free(val);
    }
  }

  free(l);
}

void *search_lista(Lista l, int (*compar)(void* a, void *b), void *comparado) {
  Node n;
  for (n = get_first(l); n != NULL; n = get_next(l, n)) {
    if (compar(get(l, n), comparado) == 1) {
      return get(l, n);
    }
  }

  return NULL;
}

void *seek_and_destroy_lista(Lista l, int (*compar)(void* a, void *b), void *comparado) {
  Node n;
  for (n = get_first(l); n != NULL; n = get_next(l, n)) {
    if (compar(get(l, n), comparado) == 1) {
      return remove_at(l, n);
    }
  }
  return NULL;
}