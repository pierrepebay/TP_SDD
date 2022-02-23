#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semaine.h"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        semaine_t *tete_semaine = createAgendaFromFile(argv[1]);
        //printAll(tete_semaine);
        //freeAll(tete_semaine);
        saveListFile(tete_semaine, "test.txt");
        jourList_t * list_jours = createJourList(tete_semaine, "Test", 20);
        printJourList(list_jours);
    }
    else
    {
        printf("Usage: %s <file_path>\n", argv[0]);
    }
}
