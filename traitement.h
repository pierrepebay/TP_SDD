#ifndef TRAITEMENT_HEADER_
#define TRAITEMENT_HEADER_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct action{
    char jour[2];
    char heure[3];
    char nom[11];
    struct action * action_suiv;
} action_t;

typedef struct semaine{
    char annee[5];
    char num_semaine[3];
    action_t * action;
    struct semaine * semaine_suiv;
} semaine_t;

void fgets2(char * ligne, int n, FILE * file);

void writeYear(semaine_t * psemaine, char * ligne);

void writeWeek(semaine_t * psemaine, char * ligne);

void writeDay(action_t * paction, char * ligne);

void writeHour(action_t * paction, char * ligne);

void writeName(action_t * paction, char * ligne);

int compareDates(action_t * paction, action_t * cour);

int compareSem(semaine_t * psemaine, semaine_t * cour);

void printActionList(action_t * action_tete);

void printAll(semaine_t * semaine_fictive);

void addActionToList(action_t * action_tete, action_t * paction);

semaine_t * addSemaineToList(semaine_t * semaine_tete, semaine_t * semaine_to_add);

semaine_t * getSemainePtr(semaine_t * semaine_tete, semaine_t * semaine_cour);

void freeAll(semaine_t semaine_tete);

#endif
