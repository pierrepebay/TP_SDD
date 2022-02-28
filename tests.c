#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semaine.h"

int test_null()
{
  semaine_t* tete_semaine = createAgendaFromFile("nulltest.txt");
  printAll(tete_semaine);
  saveListFile(tete_semaine, "nulltest_res.txt");
  jourList_t*  list_jours = createJourList(tete_semaine, "Test", 2);
  int res;
  if (list_jours->deb == NULL)
  {
    printf("Résultat correct : liste vide :\n");
    printJourList(list_jours);
    res = 0;
  }
  else
  {
    printf("Résultat incorrect : liste trouvée :\n");
    printf("%p\n", list_jours->deb);
    printJourList(list_jours);
    res = 1;
  }
  freeAll(tete_semaine, list_jours);
  return res;
}

int test_incorrect_format()
{
  int res = 0;
  return res;
}
