#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "traitement.h"

int main(){
    char ligne[21];
    FILE * file = fopen("data.txt", "r");
    semaine_t semaine_tete;
    semaine_tete.semaine_suiv = NULL;    
    if (file){
        while (!feof(file) && fgets(ligne,21,file) != NULL){
            action_t * action_cour = (action_t *)malloc(sizeof(action_t));
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
            fflush(stdout);
            if (semaine_cour == NULL){
                semaine_cour = semaine_tmp;
                semaine_cour->action = action_cour;
                addSemaineToList(&semaine_tete, semaine_cour);
                //printActionList(action_cour);
            }
            else {
                addActionToList(semaine_cour->action, action_cour);
                //printActionList(semaine_cour->action);
            }
        }
        printAll(&semaine_tete);

    }
}