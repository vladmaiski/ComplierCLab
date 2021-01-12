#include <stdio.h>
#include <stdlib.h>
#include "GRAMMAR.c"


int main() {
    tokens = malloc(256 * sizeof(TOKEN));
    if (!yylex()) {
        int result = parse();
        result ? puts("Correct") : printf("Syntax error\n");
    } else {
        puts("A lexical error was found.");
    }
    system("pause");
    return 0;
}