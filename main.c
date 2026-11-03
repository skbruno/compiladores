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