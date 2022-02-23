#ifndef ACTION_HEADER_
#define ACTION_HEADER_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct action
{
    char jour;
    char heure[2];
    char nom[10];
    struct action *action_suiv;
} action_t;

void writeDay(action_t *, char *);

void writeHour(action_t *, char *);

void writeName(action_t *, char *);

int compareDates(char, char *, action_t *);

void printActionList(action_t *);

void addActionToList(action_t *, action_t *);

void freeActions(action_t *);

#endif
