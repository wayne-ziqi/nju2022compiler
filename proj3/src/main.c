#include <stdio.h>
#include "./semantic/sdt.h"
#include "./ir/irt.h"

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

//    for (int i = 1; i <= argc - 1; i++) {
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror(argv[1]);
        return -1;
    }
//        char c;
//        while(fscanf(file,"%c",&c)!=EOF) printf("%c",c);
    // parser starts here
    yyrestart(file);
    yylineno = 1;  // should reset the line number after file changed
    // printf("%d ", yylineno);
    yyparse();
    int sem_error = 1;
    // semantic starts here
    if (!syn_error)
        sem_error = do_sdt();
    if (!sem_error) {
        do_irt();
        if (argc >= 3)
            store_ir(argv[2]);
    }

    fclose(file);
//    }
    return 0;
}