#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semaine.h"

int main(int argc, char * argv[]){
    char ligne[21];
    if (argc == 2){
        FILE * file = fopen(argv[1], "r");
        semaine_t semaine_tete;
        semaine_tete.semaine_suiv = NULL;
        if (file){
            while (!feof(file) && fgets(ligne,21,file) != NULL){
                action_t * action_cour = (action_t *)malloc(sizeof(action_t));
                action_cour->action_suiv = NULL;
                semaine_t * semaine_tmp = (semaine_t *)malloc(sizeof(semaine_t));

                //gestion de la ligne
                writeYear(semaine_tmp, ligne);
                writeWeek(semaine_tmp, ligne);
                writeDay(action_cour, ligne);
                writeHour(action_cour, ligne);
                writeName(action_cour, ligne);
                //fin gestion ligne

                semaine_t * semaine_cour = getSemainePtr(&semaine_tete, semaine_tmp);
                //printf("%p \n", semaine_cour);
                if (semaine_cour == NULL){
                    semaine_cour = semaine_tmp;
                    semaine_cour->action = action_cour;
                    addSemaineToList(&semaine_tete, semaine_cour);
                    //printActionList(action_cour);
                }
                else {
                    addActionToList(semaine_cour->action, action_cour);
                    free(semaine_tmp);
                    //printActionList(semaine_cour->action);
                }
            }
            printAll(&semaine_tete);
            removeActionFromList(&semaine_tete, "2002", "10", "3", "09");
            printf("-------------");
            printAll(&semaine_tete);
            saveListFile(&semaine_tete, "test.txt");
            freeAll(semaine_tete);
        }
    }
    else {
        printf("Usage: %s <file_path>\n", argv[0]);
    }
}
