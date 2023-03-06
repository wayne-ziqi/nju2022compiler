#include <stdio.h>
#include "./semantic/sdt.h"
#include "dataset.h"

void yyrestart(FILE *);

int yyparse();

extern int yylineno;
unsigned syn_error;

int main(int argc, char **argv) {
    if (argc < 2) {
        // printf("%d ", yylineno);
        yyparse();
        return 0;
    }

    for (int i = 1; i <= argc - 1; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            perror(argv[i]);
            return -1;
        }
        // parser starts here
        yyrestart(file);
        yylineno = 1;  // should reset the line number after file changed
        // printf("%d ", yylineno);
        yyparse();

        // semantic starts here
        if (!syn_error)
            do_sdt();
        fclose(file);
    }
    return 0;
}