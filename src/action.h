#ifndef ACTION_HEADER_
#define ACTION_HEADER_

#include "utilities.h"

#define LEN_DAY 1
#define LEN_HOUR 2
#define LEN_TASK_NAME 10

typedef struct action
{
    char day;
    char heure[LEN_HOUR];
    char nom[LEN_TASK_NAME];
    struct action* action_suiv;
} action_t;

void writeDay(action_t*, char*);

void writeHour(action_t*, char*);

void writeName(action_t*, char*);

int compareDates(char, char*, action_t*);

void printActionList(action_t*);

void addActionToList(action_t*, action_t*);

void freeActions(action_t*);

#endif
