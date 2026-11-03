#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Analex.h"

#define TAM_LEXEMA 31
#define TAM_LITERAL 200

int contLinha = 1;

void errorLex(int contLinha, char caracter)
{
    char c_str[2];
    c_str[0] = caracter;
    c_str[1] = '\0';
    printf("\nCaracter '%s' invalido na linha: %d\n", c_str, contLinha);
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

 