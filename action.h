#ifndef ACTION_HEADER_
#define ACTION_HEADER_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct action{
    char jour[2];
    char heure[3];
    char nom[11];
    struct action * action_suiv;
} action_t;

void writeDay(action_t * paction, char * ligne);

void writeHour(action_t * paction, char * ligne);

void writeName(action_t * paction, char * ligne);

int compareDates(char * jour, char * heure, action_t * cour);

void printActionList(action_t * action_tete);

void addActionToList(action_t * action_tete, action_t * paction);

void freeActions(action_t * action_tete);

void printn(char *, int);
#endif
