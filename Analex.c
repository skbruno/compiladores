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

TOKEN Analex(FILE *fd) 
{ 
    int estado = 0;
    char c;
    char lexema[TAM_LEXEMA] = "";
    int tamL = 0;
    char digitos[TAM_LITERAL] = "";
    int tamD = 0;
    TOKEN t;


    while(1)
    {
        c = fgetc(fd);

        switch(estado)
        {
            case 0:
                if(c == ' ' || c == '\t' || c == '\r')
                    estado = 0;
                else if (c == '\n')
                {
                    estado = 0;
                    contLinha++; /*Verificador de contador de linhas*/
                }
            else if (isalpha(c)) /*verificar o identificador*/
            {
                estado = 20;
                lexema[tamL++] = c;
                lexema[tamL] = '\0';
            }
            else if (isdigit(c))
            {
                estado = 22;
                digitos[tamD++] = c;
                digitos[tamD] = '\0';
            }
            else if (c == '=')  
                estado = 1;
            else if (c == '>')  
                estado = 4;
            else if (c == '<')  
                estado = 7;
            else if (c == '/')  
                estado = 17;
            else if (c == '"')  
                estado = 27;
            else if (c == '.')  
                estado = 30;
            else if (c == '\'') 
                estado = 43;
            else if (c == '+')
            {
                estado = 10;
                t.cat = SN;
                t.codigo = ADICAO;
                return t
            }
            else if (c == '-')
            {
                estado = 11;
                t.cat = SN;
                t.codigo = SUBTRACAO;
                return t
            }
            else if (c == '*')
            {
                estado = 12;
                t.cat = SN;
                t.codigo = MULTIPLICACAO;
                return t
            }
            else if (c == '(')
            {
                estado = 13;
                t.cat = SN;
                t.codigo = ABRE_PARENTESES;
                return t
            }
            else if (c == ')')
            {
                estado = 14;
                t.cat = SN;
                t.codigo = FECHA_PARENTESES;
                return t
            }
            else if (c == ',')
            {
                estado = 15;
                t.cat = SN;
                t.codigo = VIRGULA;
                return t
            }
            else if (c == '#')
            {
                estado = 16;
                t.cat = SN;
                t.codigo = DIFERENTE;
                return t
            }
            else if (c == EOF)
            {
                estado = 28;
                t.cat = FIM_ARQ;
                return t;
            }
            else
                errorLex(contLinha, c);
                break;
            case 1:
                if (c == '=')  /* recebeu um = antes */
                {
                    estado = 2;
                    t.cat = SN;
                    t.codigo = IGUAL;
                    return t;
                }
                else  /* apenas um = */
                {
                    estado = 3;
                    ungetc(c, fd);
                    t.cat = SN;
                    t.codigo = ATRIB;
                    return t;
                }
                break;

            case 4:  /* recebeu um > antes */
                if (c == '=')
                {
                    estado = 5;
                    t.cat = SN;
                    t.codigo = MAIOR_IGUAL;
                    return t;
                }
                else
                {
                    estado = 6;
                    ungetc(c, fd);
                    t.cat = SN;
                    t.codigo = MAIOR;
                    return t;
                }
                break;

            case 7:  /* recebeu um > antes */
                if (c == '=')
                {
                    estado = 8;
                    t.cat = SN;
                    t.codigo = MENOR_IGUAL;
                    return t;
                }
                else
                {
                    estado = 9;
                    ungetc(c, fd);
                    t.cat = SN;
                    t.codigo = MENOR;
                    return t;
                }
                break;
            case 17:  /* recebeu um / antes */
                if (c == '/')
                    estado = 19;
                else
                {
                    estado = 18;
                    ungetc(c, fd);
                    t.cat = SN;
                    t.codigo = DIVISAO;
                    return t;
                }
                break;
            case 19:  /* recebeu um / antes e finalizar ou comentario*/
                if (c == '\n' || c == EOF)
                {
                    ungetc(c, fd);
                    estado = 44;
                }
                else
                    estado = 19;
                break;
            case 30:
                if (c == 'a')
                    estado = 31;
                else if (c == 'o')
                    estado = 32;
                else if (c == 'n')
                    estado = 33;
                else
                    errorLex("Operador logico invalido");
                break;

            case 31:
                if (c == 'n')
                    estado = 34;
                else
                    errorLex("Operador logico invalido, esperado and");
                break;

            case 34:
                if (c == 'd')
                    estado = 35;
                else
                    errorLex("Operador logico invalido, esperado and");
                break;

            case 35:
                if (c == '.')
                {
                    estado = 36;
                    t.cat = SN;
                    t.codigo = AND;
                    return t;   /* Final operador and */
                }
                else
                    errorLex("Operador logico invalido, esperado and");
                break;

            case 32:
                if (c == 'r')
                    estado = 37;
                else
                    errorLex("Operador logico invalido, esperado or");
                break;

            case 37:
                if (c == '.')
                {
                    estado = 38;
                    t.cat = SN;
                    t.codigo = OR;
                    return t;   /* Final operador or */
                }
                else
                    errorLex("Operador logico invalido, esperado or");
                break;

            case 33:
                if (c == 'o')
                    estado = 39;
                else
                    errorLex("Operador logico invalido, esperado not");
                break;

            case 39:
                if (c == 't')
                    estado = 40;
                else
                    errorLex("Operador logico invalido, esperado not");
                break;

            case 40:
                if (c == '.')
                {
                    estado = 41;
                    t.cat = SN;
                    t.codigo = NOT;
                    return t;   /* Final operador not */
                }
                else
                    errorLex("Operador logico invalido, esperado not");
                break;
        }
    }


}

 