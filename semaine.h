#ifndef SEMAINE_HEADER_
#define SEMAINE_HEADER_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "action.h"

typedef struct semaine
{
    char annee[5];
    char num_semaine[3];
    action_t *action;
    struct semaine *semaine_suiv;
} semaine_t;

typedef struct jourList
{
    char *deb;
    char *fin;
    int tailleMax;
} jourList_t;

#include "agenda.h"

void writeYear(semaine_t *, char *);

void writeWeek(semaine_t *, char *);

int compareSem(char *, char *, semaine_t *);

void printAll(semaine_t *);

void removeActionFromList(semaine_t *, char *, char *, char, char *);

void addSemaineToList(semaine_t *, semaine_t *);

semaine_t *getSemainePtr(semaine_t *, semaine_t *);

void freeWeek(semaine_t *);

void freeAll(semaine_t *, jourList_t *);

void saveListFile(semaine_t *, char *);

int motifPresent(char *, char *);

jourList_t *createJourList(semaine_t *, char *, int);

#endif
