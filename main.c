#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Analex.h"

FILE *fd;
TOKEN tk;

void Analisador_PL(FILE *fd)
{
    printf("\n[== Analisador PL ==]\n");
    tk = Analex(fd);
    while (tk.cat != FIM_ARQ)
    {
        switch (tk.cat)
        {
        case ID:
            printf("<ID, %s>\n", tk.lexema);
            break;
        case PR:
            printf("<PR, %d>\n", tk.codigo);
            break;
        case SN:
            printf("<SN, %d>\n", tk.codigo);
            break;
        case CT_I:
            printf("<CT_I, %d>\n", tk.valInt);
            break;
        case CT_R:
            printf("<CT_R, %f>\n", tk.valReal);
            break;
        case CT_C:
            printf("<CT_C, %d>\n", tk.caracter);
            break;
        case LT:
            printf("<LT, \"%s\">\n", tk.literal);
            break;
        default:
            break;
        }
        tk = Analex(fd);
    }
    printf("<FIM_ARQ>\n");
}

int main()
{
    fd = fopen("teste.dat", "r");

    if (fd == NULL)
    {
        fprintf(stderr, "\nError ao abrir o arquivo\n");
        return 1;
    }

    Analisador_PL(fd);
    fclose(fd);
    return 0;
}
