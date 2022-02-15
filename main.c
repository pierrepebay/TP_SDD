#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semaine.h"

int main(int argc, char * argv[]){
    char ligne[21];
    if (argc == 2){
      FILE * file = fopen(argv[1], "r");
      semaine_t * semaine_tete = (semaine_t *)malloc(sizeof(semaine_t));  // tête fictive de la liste des semaines
      semaine_tete->semaine_suiv = NULL;
      action_t * action_cour;
      semaine_t * semaine_tmp;
      if (file){
          while (!feof(file) && fgets(ligne,21,file) != NULL){ // lecture du fichier et écriture de chaque ligne dans la chaîne de caractères "ligne"
              action_cour = (action_t *)malloc(sizeof(action_t));
              action_cour->action_suiv = NULL;
              semaine_tmp = (semaine_t *)malloc(sizeof(semaine_t));

              // écriture des informations que contient la ligne dans les champs adéquats
              writeYear(semaine_tmp, ligne);
              writeWeek(semaine_tmp, ligne);
              writeDay(action_cour, ligne);
              writeHour(action_cour, ligne);
              writeName(action_cour, ligne);

              semaine_t * semaine_cour = getSemainePtr(semaine_tete, semaine_tmp); // recherche si la semaine appartient à la liste des semaines
              if (semaine_cour == NULL){ // si la semaine n'appartient pas à la liste des semaines
                  semaine_cour = semaine_tmp;
                  semaine_cour->action = action_cour;
                  addSemaineToList(semaine_tete, semaine_cour);
              }
              else { // si la semaine est déjà présente dans la liste des semaines
                  addActionToList(semaine_cour->action, action_cour);
                  free(semaine_tmp); // on libère la semaine temporaire
              }
          }
          //printAll(semaine_tete);
          //removeActionFromList(semaine_tete, "2002", "10", "3", "09");
          printAll(semaine_tete);
          //saveListFile(semaine_tete, "test.txt");
          freeAll(semaine_tete);
          fclose(file);
        }
    }
    else {
        printf("Usage: %s <file_path>\n", argv[0]);
    }
}
