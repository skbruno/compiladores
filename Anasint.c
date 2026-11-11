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
    if (tk.cat == PR && (tk.codigo == PR_CHAR || tk.codigo == PR_INT || tk.codigo == PR_REAL || tk.codigo == PR_BOOL))
    {
        tk = Analex(fd);
        return true;
    }
    else
        return false;
}

void decl_var()
{
    if (tk.cat != ID)
        errorSint("Identificador esperado na declaracao de variavel");
    tk = Analex(fd);
}

bool TipoDeclVar()
{
    if (!tipo())
        return false;

    decl_var();
    while (tk.cat == SN && tk.codigo == VIRGULA)
    {
        tk = Analex(fd);
        decl_var();
    }
    return true;
}
