#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semaine.h"
#include "tests.h"
#include "jeu_de_test.h"


int main(int argc, char* argv[])
{
    int res;
    if (argc == 2)
    {
        semaine_t* tete_semaine = createAgendaFromFile(argv[1]);
        printAll(tete_semaine);
        saveListFile(tete_semaine, "test.txt");
        jourList_t*  list_jours = createJourList(tete_semaine, "Test", 2);
        printJourList(list_jours);
        freeAll(tete_semaine, list_jours);
        res = 0;
    }
    else
    {
      run_tests();
    }
    return res;
}
