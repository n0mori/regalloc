#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Nick_string.h"

int bn = 0;
void prt() {
    if (!bn) {
        bn = 1;
    } else {
        printf("\n");
    }
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

int main() {
    char buffer[10000];
    FILE *p = NULL;
    int active = 0;

    for (;;) {
        char *token;

        fgets(buffer, 10000, stdin);

        if (buffer[0] == 'G') {
            if (active) {
                pclose(p);
            }

            active = 1;
            p = popen("./main", "w");
            fprintf(p, "%s", buffer);
        } else {
            fprintf(p, "%s", buffer);
        }


        if (feof(stdin)) {
            break;
        }

        buffer[0] = 0;
    }

    if (p != NULL) {
        pclose(p);
    }

}