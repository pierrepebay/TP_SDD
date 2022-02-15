#ifndef SEMAINE_HEADER_
#define SEMAINE_HEADER_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "action.h"


typedef struct semaine{
    char annee[5];
    char num_semaine[3];
    action_t * action;
    struct semaine * semaine_suiv;
} semaine_t;

typedef struct jourList{
    char * deb;
    char * fin;
    int tailleMax;
} jourList_t;

void writeYear(semaine_t * psemaine, char * ligne);

void writeWeek(semaine_t * psemaine, char * ligne);

int compareSem(char * annee, char * num_semaine, semaine_t * cour);

void printAll(semaine_t * semaine_fictive);

void removeActionFromList(semaine_t * semaine_fictive, char * annee, char * semaine, char jour, char * heure);

void addSemaineToList(semaine_t * semaine_tete, semaine_t * semaine_to_add);

semaine_t * getSemainePtr(semaine_t * semaine_tete, semaine_t * semaine_cour);

void freeWeek(semaine_t * semaine_courante);

void freeAll(semaine_t * semaine_tete);

void saveListFile(semaine_t * semaine_tete, char * file_name);

int motifPresent(char * nom, char * motif);

jourList_t * createJourList(semaine_t * semaine_tete, char * motif, int taillemax);

#endif
