#include <stdio.h>
#include <common.h>
#include "compiler.h"
#include "scanner.h"

void compile(const char* source) {
    
    initScanner(source);

    int line = -1;
    for (;;) {

        Token token = scanToken();
        if (token.line != line) {
            printf("%4d", token.line);
            line = token.line;
        }
        else {
            printf("   | ");
        }

        printf("%2d '%.*s'\n", token.type, token.length, token.start); // 印出token 資訊;
        if (token.type == TOKEN_EOF) {
            break;
        }

    }
}