#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h> 
#include <stdbool.h> 
#include "Analex.h"

#define TAM_LEXEMA 31
#define TAM_LITERAL 200


void error(char msg[]) { 
    printf("%s\n", msg); 
    exit(1); 
}

TOKEN AnaLex(FILE *fd) { 
    int estado = 0;
    char c;
    char lexema[TAM_LEXEMA] = "";
    int tamL = 0;
    char digitos[TAM_LITERAL] = "";
    char tamD = 0;
    TOKEN t;


    while(1){
        c = fgetc(fd);

        switch(estado){

            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
        }
    }


}

 