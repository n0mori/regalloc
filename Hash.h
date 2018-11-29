#ifndef HASH__H
#define HASH__H

/* 
Este é o módulo que implementará a tabela de espalhamento (Hash). Uma tabela de espalhamento
é uma maneira eficaz de fazer buscas em um conjunto de dados. A tabela de espalhamento associa
uma chave a um dado para inserir e retirar esses dados da tabela.
*/

#include "Lista.h"
#include <string.h>
#include <stdio.h>

typedef void* Hash;

Hash new_hash(int size); /* Retorna uma nova tabela de espalhamento */
void hash_insert(Hash hash, char* key, void* data); /* Insere o dado na tabela e o associa à chave passada */
void *hash_get(Hash hash, char *key); /* Retorna o dado associado à chave passada, ou NULL se não houver dado associado à chave. */
void *hash_delete(Hash hash, char *key); /* Remove o dado associado à chave passada e o retorna */
void hash_free(Hash hash, void (*destroy)(void *a)); /* Remove e desaloca a tabela inteira, Usa o método destroy passado para desalocar os dados */
void hash_filter(Hash hash, Lista filtrados, int (*cmp)(void *a, void *b), void *comparado);
void hash_delete_all(Hash hash);

#endif
