#ifndef ANALEX_H
#define ANALEX_H
#include <stdio.h>
#define TAM_MAX_LEXEMA 31
#define TAM_MAX_LITERAL 200

enum TOKEN_CAT {
    ID = 1, /*Identificador*/
    PR, /*Palavra reservada*/
    SN, /*Sinais*/
    LT, /*literal*/
    CT_I, /*Constante inteira*/
    CT_R, /*Constante real*/
    CT_C, /*Caracter*/
    FIM_ARQ /*fim*/
};

enum SINAIS {
    ATRIB = 1,
    IGUAL,
    ADICAO,
    SUBTRACAO,
    MULTIPLICACAO,
    DIVISAO,
    MENOR,
    MENOR_IGUAL,
    MAIOR,
    MAIOR_IGUAL,
    ABRE_PARENTESES,
    FECHA_PARENTESES,
    VIRGULA,
    AND,
    OR,
    NOT,
    DIFERENTE
};

enum PALAVRAS_RESERVADAS{
    PR_PL = 1,
    PR_VAR,
    PR_ENDVAR,
    PR_PROG,
    PR_ENDPROG,

    PR_CHAR,
    PR_INT,
    PR_REAL,
    PR_BOOL,

    PR_FWD,
    PR_PROC,
    PR_ENDPROC,
    PR_ENDFUNC,
    PR_NOPARAM,

    PR_IF,
    PR_ELSE,
    PR_ENDIF,
    PR_WHILE,
    PR_ENDWHILE,
    PR_RETURN,
    PR_CALL,
    PR_KEYBOARD,
    PR_DISPLAY,
    PR_DUP
};

typedef struct {
    enum TOKEN_CAT cat;
    union {
        int codigo;
        char lexema[TAM_MAX_LEXEMA]; 
        int indice;
        int valInt; 
        float valReal;
        char caracter;
        char literal[TAM_MAX_LITERAL];
    };
} TOKEN;

extern TOKEN tk;
extern FILE *fd;
extern int contLinha;
TOKEN Analex(FILE *);

#endif


