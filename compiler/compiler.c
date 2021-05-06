/* cREXX Phase 0 (PoC) Compiler */
/* (c) Adrian Sutherland 2021   */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "compiler.h"

int main(int argc, char *argv[]) {

    FILE *fp, *traceFile = 0;
    char *buff;
    size_t bytes;
    int token_type, last_token_type;
    Token *token;
    Context context;
    void *parser;

    /* Open input file */
    if (argc==2)   fp = fopen(argv[1], "r");
    else fp = NULL;
    if (fp == NULL) {
        fprintf(stderr, "Can't open input file\n");
        exit(-1);
    }

    /* Open trace file */
#ifndef NDEBUG
    traceFile = fopen("rxtrace.txt", "w");
    if(traceFile == NULL) {
        fprintf(stderr, "Can't open trace file\n");
        exit(-1);
    }
#endif

    /* Get file size */
    fseek(fp, 0, SEEK_END);
    bytes = ftell(fp);
    rewind(fp);

    /* Allocate buffer and read */
    buff = (char*) malloc(bytes * sizeof(char));
    bytes = fread(buff, 1, bytes, fp);
    if (!bytes) {
        fprintf(stderr, "Error reading input file\n");
        exit(-1);
    }

    /* Initialize context */
    context.traceFile = traceFile;
    context.top = buff;
    context.cursor = buff;
    context.linestart = buff;
    context.line = 0;
    context.token_head = 0;
    context.token_tail = 0;
    context.token_counter = 0;
    context.ast = 0;
    context.free_list = 0;
    context.level = UNKNOWN;
    context.buff_end = (char*) (((char*)buff) + bytes);

    /* Create Options parser to work out required language level */
    opt_pars(&context);

    /* Deallocate memory and reset context */
    free_tok(&context);
    context.top = buff;
    context.cursor = buff;
    context.linestart = buff;
    context.line = 0;
    context.token_head = 0;
    context.token_tail = 0;
    context.token_counter = 0;
    context.ast = 0;
    context.free_list = 0;

    /* Parse program for real */
    switch (context.level){
        case LEVELA:
        case LEVELC:
        case LEVELD:
            printf("REXX Level A/C/D (Classic Rexx) - Not supported yet\n");
            break;

        case LEVELB:
        case LEVELG:
        case LEVELL:
            printf("REXX Level B/G/L (cREXX)\n");
            rexbpars(&context);
            break;

        default:
            printf("Internal Error - Failed to determine REXX Level\n");
    }


    if (!context.ast) {
        printf("Compiler Exiting - Failure\n");
        goto finish;
    }
/*
    prnt_ast(context.ast);
    printf("\n");
*/
    pdot_tree(context.ast, "astgraph0.dot");
    /* Get dot from https://graphviz.org/download/ */
    system("dot astgraph0.dot -Tpng -o astgraph0.png");

    validate(&context);

    pdot_tree(context.ast, "astgraph1.dot");
    system("dot astgraph1.dot -Tpng -o astgraph1.png");

    /* Generate Assembler */
    printf("Generating Assembler\n");
    emit(&context, "output.rxas");

    pdot_tree(context.ast, "astgraph2.dot");
    system("dot astgraph2.dot -Tpng -o astgraph2.png");


    printf("Compiler Exiting - Success\n");

    finish:
    /* Deallocate AST */
    free_ast(&context);

    /* Deallocate Tokens */
    free_tok(&context);

    /* Close files and deallocate */
    fclose(fp);
#ifndef NDEBUG
    fclose(traceFile);
#endif
    free(buff);


    return(0);
}
