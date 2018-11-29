#include "Nick_string.h"

char *monta_arquivo(char *dir, char *a, char *e) {
  char *str = malloc(sizeof(char) * (strlen(dir) + strlen(a) + strlen(e) + 2));
  sprintf(str, "%s%s.%s", dir, a, e);
  return str;
}

char *pega_path(char *str) {
  char *buffer = malloc(MAX_BUFFER * sizeof(char));
  sscanf(str, "%*c%*c%s", buffer);
  return buffer;
}

char *substitui_str(char *str, char *new) {
  free(str);
  str = malloc(sizeof(char) * (strlen(new) + 1));
  strcpy(str, new);
  return str;
}

char *limpa(char *str) {
  free(str);
  return alloc_inicial();
}

char *alloc_inicial() {
  char *str = malloc(sizeof(char));
  *str = 0;
  return str;
}

char *concatena(char *inicio, char *fim) {
  inicio = (char *) realloc(inicio, sizeof(char) * (strlen(inicio) + strlen(fim) + 1));
  strcat(inicio, fim);
  return inicio;
}

char *pega_string(char *str) {
  char *buffer = malloc(MAX_BUFFER * sizeof(char));
  sscanf(str, "%*c%*c\"%[^\"]", buffer);
  return buffer;
}

int interpreta_t1(char *str) {
  switch (str[0]) {
    case 'x':
      return 1;
      break;
    case 'y':
      return 2;
      break;
    case 'z':
      return 3;
      break;
    case 'l':
      switch (str[1]) {
        case 'x':
          return 4;
          break;
        case 'y':
          return 5;
          break;
        case 'z':
          return 6;
          break;
      }
      break;
    case 'd':
      return 7;
      break;
    case 'a':
      return 8;
      break;
    case 'e':
      return 9;
      break;
    case 'c':
      return 10;
      break;
    case 'o':
      return 11;
      break;
    case 'w':
      return 12;
      break;
    case 'f':
      return 13;
      break;
  }
  return 0;
}

char *le_linha(FILE *f) {
  char *str = calloc(MAX_BUFFER, sizeof(char));
  fgets(str, MAX_BUFFER, f);
  return str;
}

char *arruma_dir(char *dir) {
  if (dir[strlen(dir) - 1] != '/') {
    dir = concatena(dir, "/");
  }
  return dir;
}

void verifica_quebras(char *str) {
  int i;
  for (i = 0; i < strlen(str); i++) {
    if (str[i] == '\\' && str[i + 1] == 'n') {
      str[i] = ' ';
      str[i + 1] = '\n';
    }
  }
}

char *last_slash(char *s) {
  char *c = NULL;
  int i;
  for (i = 0; i < strlen(s); i++) {
    if (s[i] == '/') {
      c = &s[i];
    }
  }
  return c;
}

void retira_extensao(char *s) {
  int i;
  for (i = strlen(s) - 1; i >= 0; i--) {
    if (s[i] == '.') {
      s[i] = 0;
      return;
    }
  }
}

int busca_slash(char *s) {
  int i;
  for (i = 0; i < strlen(s); i++) {
    if (s[i] == '/') {
      return 1;
    }
  }
  return 0;
}

void retira_path(char *s) {
  int i;
  while (busca_slash(s)) {
    for (i = 0; i < strlen(s); i++) {
      s[i] = s[i + 1];
    }
  }
}
