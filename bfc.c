#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* input_file;
char* output_file;
char* tmp_file = ".tmp.c";
FILE* fpi = NULL;
FILE* fpo = NULL;

void compile();
void showhelp();
void showversion();


int main(int argc, char** argv){
    // check args
    if(argc<2){
        printf("fatal error: no input file\n");
        showhelp();
        exit(-1);
    }
    if(strcmp(argv[1], "-h")==0){
        showhelp();
        exit(-1);
    }
    if(strcmp(argv[1], "-v")==0){
        showversion();
        exit(-1);
    }
    if(argc==2){
        printf("fatal error: no input file\n");
        showhelp();
        exit(-1);
    }
    input_file = argv[1];
    output_file = argv[2];
    fpi = fopen(input_file, "r");
    fpo = fopen(tmp_file, "w");
    if(fpi==NULL){
        printf("fatal error: unable to open input file %s\n", input_file);
        exit(-1);
    }
    if(fpo==NULL){
        printf("fatal error: unable to open output file %s\n", input_file);
        exit(-1);
    }
    compile();
    fclose(fpi);
    fclose(fpo);
    char* cmdbuf = (char*)malloc(1024);
    sprintf(cmdbuf, "gcc .tmp.c -o %s", output_file);
    system(cmdbuf);
    //system("rm .tmp");
}

void showhelp(){
    printf("usage: bfc [options] [input file] [output file]\n");
    printf("options:\n");
    printf("  -h  show this message\n");
    printf("  -v  show version info\n");
}

void showversion(){
    printf("brinfuck compiler v1.0\n");
    printf("author: Jar36 (https://github.com/Jar387/brainf-k-compiler)\n");
    printf("this software is published under GPLv3 license. All rights reserved\n");
}

void compile(){
    // init output c source
    fputs("#include \"target_rsrc.c\"\n", fpo);
    fputs("void main(){\n", fpo);
    int c = fgetc(fpi);
    while (c != EOF) {
        char op = (char)c;
        if (op == '>') {
            fputs("    pinc();\n", fpo);
        }
        if (op == '<') {
            fputs("    pdec();\n", fpo);
        }
        if (op == '+') {
            fputs("    inc();\n", fpo);
        }
        if (op == '-') {
            fputs("    dec();\n", fpo);
        }
        if (op == '.') {
            fputs("    out();\n", fpo);
        }
        if (op == ',') {
            fputs("    in();\n", fpo);
        }
        if (op == '[') {
            fputs("    while (*ptr) {\n", fpo);
        }
        if (op == ']') {
            fputs("    }\n", fpo);
        }
        c = fgetc(fpi);
    }
    fputs("}\n", fpo);
}