#include <stdio.h>
#include <stdlib.h>
#include "Analex.h"
#include "Anasint.h"

static void errorSint(char *msg)
{
    printf("\nErro sintatico: %s na linha %d\n", msg, contLinha);
    exit(1);
}
bool tipo()
{
    if (tk.cat == PR && (tk.codigo == CHAR || tk.codigo == INT || tk.codigo == REAL || tk.codigo == BOOL))
    {
        tk = analexPL(fd);
        tratado = true;
        return true;
    }
    else
        return false;
}

void decl_var()
{
    if (tk.cat != ID)
        error("Identificador esperado na declaracao de variavel");
    tratado = true;
    tk = analexPL(fd);
}

bool TipoDeclVar()
{
    if (!tipo())
        return false;

    decl_var();
    while (tk.cat == SN && tk.codigo == VIRGULA)
    {
        tk = analexPL(fd);
        decl_var();
        tratado = true;
    }
    return true;
}
