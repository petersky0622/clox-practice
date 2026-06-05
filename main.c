#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

static void repl(){
    char line[1024];
    for (;;) {
        printf("> ");

        if (!(fgets(line, sizeof(line), stdin))) {
            printf("\n");
            break;
        }
        interpret(line);
    }
}

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");                                            // 1. 以「唯讀」且「二進位 (Binary)」模式打開檔案水管。
    
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }                                                                           //    使用 "rb" 是為了強迫作業系統原封不動讀出原始位元組，
                                                                               //    防止系統自動將 \r\n 轉換為 \n，導致後續測量的 fileSize 與實際讀入的字元數對不上
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);  //倒帶到檔案開頭

    char* buffer = (char*)malloc(fileSize + 1);                 // 因為\0

    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

static void runFile(char* path) {
    char* source = readFile(source);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}


int main(int argc, const char *argv[])
{
    initVM();

    if (argc == 1) {
        repl();
    }
    else if (argc == 2) {
        runFile(argv[1]);
    }
    else {
        fprintf(stderr, "Usage: clox [path]\n");
        exit(64);
    }

    freeVM();
    

    return 0;
}