#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Analex.h"

#define TAM_LEXEMA 31
#define TAM_LITERAL 200

int contLinha = 1;

void errorLex(char *msg)
{
    printf("\n%s na linha: %d\n", msg, contLinha);
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
    int i;
    TOKEN t;

    while (1)
    {
        c = fgetc(fd);

        switch (estado)
        {
        case 0:
            if (c == ' ' || c == '\t' || c == '\r')
                estado = 0;
            else if (c == '\n')
            {
                estado = 0;
                contLinha++;
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
                return t;
            }
            else if (c == '-')
            {
                estado = 11;
                t.cat = SN;
                t.codigo = SUBTRACAO;
                return t;
            }
            else if (c == '*')
            {
                estado = 12;
                t.cat = SN;
                t.codigo = MULTIPLICACAO;
                return t;
            }
            else if (c == '(')
            {
                estado = 13;
                t.cat = SN;
                t.codigo = ABRE_PARENTESES;
                return t;
            }
            else if (c == ')')
            {
                estado = 14;
                t.cat = SN;
                t.codigo = FECHA_PARENTESES;
                return t;
            }
            else if (c == ',')
            {
                estado = 15;
                t.cat = SN;
                t.codigo = VIRGULA;
                return t;
            }
            else if (c == '#')
            {
                estado = 16;
                t.cat = SN;
                t.codigo = DIFERENTE;
                return t;
            }
            else if (c == EOF)
            {
                estado = 28;
                t.cat = FIM_ARQ;
                return t;
            }
            else
                errorLex("Caracter invalido na expressao");
            break;
        case 1:
            if (c == '=') /* recebeu um = antes */
            {
                estado = 2;
                t.cat = SN;
                t.codigo = IGUAL;
                return t;
            }
            else /* apenas um = */
            {
                estado = 3;
                ungetc(c, fd);
                t.cat = SN;
                t.codigo = ATRIB;
                return t;
            }
            break;

        case 4: /* recebeu um > antes */
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

        case 7: /* recebeu um < antes */
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
        case 17: /* recebeu um / antes */
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
        case 19:
            if (isalnum(c) || c == ' ')
                estado = 19;
            else if (c == '\n' || c == EOF)
            {
                ungetc(c, fd);
                estado = 0;
            }
            else
                errorLex("Caracter invalido no comentario");
            break;

        case 20: /* identificador */
            if (isalnum(c))
            {
                if (tamL >= TAM_LEXEMA - 1)
                    errorLex("Identificador invalido");
                lexema[tamL++] = c;
                lexema[tamL] = '\0';
            }
            else
            {
                estado = 21;
                ungetc(c, fd);

                for (i = 0; i < QTD_PR; i++)
                {
                    if (strcmp(lexema, palavrasReservadas[i]) == 0)
                    {
                        t.cat = PR;
                        t.codigo = i + 1;
                        return t;
                    }
                }
                t.cat = ID;
                strcpy(t.lexema, lexema);
                return t;
            }
            break;

        case 22: /* decidindo ser vai ser inteiro ou real */
            if (isdigit(c))
            {
                digitos[tamD++] = c;
                digitos[tamD] = '\0';
            }
            else if (c == '.') /* veio o ponto vai ser real */
            {
                estado = 24;
                digitos[tamD++] = c;
                digitos[tamD] = '\0';
            }
            else /*inteiro */
            {
                estado = 23;
                ungetc(c, fd);
                t.cat = CT_I;
                t.valInt = atoi(digitos);
                return t;
            }
            break;

        case 24: /* continuacao depois do ponto */
            if (isdigit(c))
            {
                estado = 25;
                if (tamD >= TAM_LITERAL - 1)
                    errorLex("Numero muito longo");
                digitos[tamD++] = c;
                digitos[tamD] = '\0';
            }
            else
                errorLex("Numero real invalido");
            break;

        case 25:
            if (isdigit(c))
            {
                digitos[tamD++] = c;
                digitos[tamD] = '\0';
            }
            else /* OUTRO: terminou o real */
            {
                estado = 26;
                ungetc(c, fd);
                t.cat = CT_R;
                t.valReal = atof(digitos);
                return t;
            }
            break;

        case 27:
            if (c == '"') /* display do literal */
            {
                estado = 29;
                t.cat = LT;
                strcpy(t.literal, digitos);
                return t;
            }
            else if (isalnum(c) || c == ' ')
            {
                digitos[tamD++] = c;
                digitos[tamD] = '\0';
            }
            else
                errorLex("Caracter invalido no literal");
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
                return t; /* Final operador and */
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
                return t; /* Final operador or */
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
                return t; /* Final operador not */
            }
            else
                errorLex("Operador logico invalido, esperado not");
            break;

        case 43:
            if (c == '\'')
            {
                estado = 44;
                t.cat = CT_C;
                t.caracter = lexema[0];
                return t;
            }
            else if (isalnum(c) || c == ' ')
            {
                if (tamL == 0) /* guarda so o primeiro caractere */
                {
                    lexema[tamL++] = c;
                    lexema[tamL] = '\0';
                }
            }
            else
                errorLex("Caracter invalido na constante caractere");
            break;
        }
    }
}
