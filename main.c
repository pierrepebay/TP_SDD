#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semaine.h"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        semaine_t *tete_semaine = createAgendaFromFile(argv[1]);
        printAll(tete_semaine);
        freeAll(tete_semaine);
    }
    else
    {
        printf("Usage: %s <file_path>\n", argv[0]);
    }
}
