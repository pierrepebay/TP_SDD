#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semaine.h"
#include "tests.h"

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
        //printf("Usage: %s <file_path>\n", argv[0]);
      int MenuOption;
      printf("Choisir le test: \n");
      printf("0: test fichier vide \n");
      printf("1: test format de date incorrect");
      scanf("%d", &MenuOption);
      switch (MenuOption) {
        case 0:
          res = test_null();
          break;
        case 1:
          res = test_incorrect_format();
          break;
      }
    }
    return res;
}
