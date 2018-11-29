#ifndef MAX_BUFFER
#define MAX_BUFFER 1000
#endif
#ifndef NICK_STRING__H
#define NICK_STRING__H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *le_linha(FILE *f);
int interpreta(char *str);
char *pega_string(char *str);
char *concatena(char *inicio, char *fim);
char *alloc_inicial();
char *limpa(char *x);
char *substitui_str(char *str, char *new);
char *pega_path(char *str);
char *monta_arquivo(char *dir, char *a, char *e);
char *arruma_dir(char *dir);
void verifica_quebras(char *str);
char *last_slash(char *str);
void retira_extensao(char *s);
int busca_slash(char *s);
void retira_path(char *s);

#endif
