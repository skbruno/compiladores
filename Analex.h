#ifndef ANALEX_H
#define ANALEX_H

#define TAM_MAX_LEXEMA 31
#define TAM_MAX_LITERAL 200

enum TOKEN_CAT {
    ID = 1, /*Identificador*/
    PR, /*Palavra reservada*/
    SN, /*Sinais*/
    CT_I, /*Constante inteira*/
    CT_R, /*Constante real*/
    CT_C, /*Caracter*/
    LT, /*literal*/
    FIM_ARQ /*fim*/
};

enum SINAIS {
    ATRIB = 1,
    IGUAL,
    ADICAO,
    SUBTRACAO,
    MULTIPLICACAO
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
    COMENTARIO
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
    PR_PARAM,
    PR_FUNCAO,
    PR_ENDFUNCAO,
    PR_PROC,
    PR_ENDPROC,
    PR_IF
    PR_ELSE,
    PR_ENDIF,
    PR_WHILE,
    PR_ENDWHILE,
    PR_RETURN,
}

typedef struct {
    enum TOKEN_CAT cat;
    union {
        int codigo;
        char lexema{TAM_MAX_LEXEMA}
        int valInt;
        float valReal;
        char valChar;
        char literal{TAM_MAX_LITERAL}
    };
} TOKEN;


#endif 
