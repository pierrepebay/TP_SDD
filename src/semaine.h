#ifndef SEMAINE_HEADER_
#define SEMAINE_HEADER_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MEME_DATE 1
#define DATE1_SUP_DATE2 2
#define DATE1_INF_DATE2 3

#define LEN_YEAR 4
#define LEN_WEEK 2

#include "action.h"


typedef struct semaine
{
    char annee[LEN_YEAR];
    char num_semaine[LEN_WEEK];
    action_t* action;
    struct semaine* semaine_suiv;
} semaine_t;

typedef struct jourList
{
    char* deb;
    char* fin;
    int tailleMax;
} jourList_t;

#include "agenda.h"

void writeYear(semaine_t*, char*);

void writeWeek(semaine_t*, char*);

int compareSem(char*, char*, semaine_t*);

void printAll(semaine_t*);

void removeActionFromList(semaine_t*, char*, char*, char, char*);

void addSemaineToList(semaine_t*, semaine_t*);

semaine_t*getSemainePtr(semaine_t*, semaine_t*);

void freeWeek(semaine_t*);

#endif
