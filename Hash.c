#include "Hash.h"

const char global_key[] = "The quick brown fox jumps over the lazy dog";
const int  global_size  = 41; 

typedef struct hash {
  int size, used;
  Lista *arr;
}* StHash;

typedef struct hashpack {
  char key[20];
  void *data;
}* HashPack;

int cmp_pack_key(void *pack, void *key) {
  HashPack p = (HashPack) pack;
  return strcmp(p->key, key) == 0;
}

int hash_index(int size, char *key) {
  int i, soma, index;
  soma = 0;
  for (i = 0; i < strlen(key); i++) {
    soma += (key[i] * i) / (global_key[i % global_size]);
  }
  index = soma % size;
  /*printf("soma: %d index: %d\n", soma, index);*/
  return index;
}

Hash new_hash(int size) {
  int i;
  StHash hash = malloc(sizeof(struct hash));
  hash->size = size;
  hash->used = 0;
  hash->arr = malloc(sizeof(Lista) * size);
  for (i = 0; i < size; i++) {
    hash->arr[i] = create_lista();
  }
  return hash;
}

void hash_insert(Hash hash, char* key, void* data) {
  StHash h = (StHash) hash;
  HashPack p = malloc(sizeof(struct hashpack));
  int index = hash_index(h->size, key);

  strcpy(p->key, key);
  p->data = data;

  insert_first(h->arr[index], p);
}

void *hash_get(Hash hash, char *key) {
  StHash h = (StHash) hash;
  int index = hash_index(h->size, key);
  HashPack p = search_lista(h->arr[index], cmp_pack_key, key);
  if (p == NULL) {
    return p;
  } else {
    return p->data;
  }
}

void *hash_delete(Hash hash, char *key) {
  StHash h = (StHash) hash;
  int index = hash_index(h->size, key);
  HashPack p = seek_and_destroy_lista(h->arr[index], cmp_pack_key, key);
  if (p == NULL) {
    return p;
  } else {
    void *data = p->data;
    free(p);
    return data;
  }
}

void hash_free(Hash hash, void (*destroy)(void *a)) {
  int i;
  StHash h = (StHash) hash;
  for (i = 0; i < h->size; i++) {
    while (length_lista(h->arr[i]) > 0) {
      HashPack p = remove_first(h->arr[i]);
      destroy(p->data);
      free(p);
    }
    free_lista(h->arr[i]);
  }
  free(h->arr);
  free(h);
}

void hash_delete_all(Hash hash) {
  int i;
  StHash h = (StHash) hash;
  for (i = 0; i < h->size; i++) {
    free_lista(h->arr[i]);
  }
  free(h->arr);
  free(h);
}

void hash_filter(Hash hash, Lista filtrados, int (*cmp)(void *a, void *b), void *comparado) {
  int i;
  StHash h = (StHash) hash;
  for (i = 0; i < h->size; i++) {
    Node n;
    for (n = get_first(h->arr[i]); n != NULL; n = get_next(h->arr[i], n)) {
      HashPack hp = get(h->arr[i], n);
      void *a = hp->data;
      if (cmp(a, comparado)) {
        insert_last(filtrados, a);
      }
    }
  }
}