#ifndef ACTION_HEADER_
#define ACTION_HEADER_

/*
Ce fichier contient la structure action ainsi que les fonctions associées.
*/

#include "utilities.h"

#define LEN_DAY 1
#define LEN_HOUR 2
#define LEN_TASK_NAME 10

typedef struct action
{
    char day;
    char hour[LEN_HOUR];
    char name[LEN_TASK_NAME];
    struct action *next_action;
} action_t;

void WriteDay(action_t *action, char *ligne);

void WriteHour(action_t *action, char *ligne);

void WriteName(action_t *action, char *ligne);

int CompareActionDates(char day, char *hour, action_t *action);

void PrintActionList(action_t *action_head);

void AddActionToList(action_t *action_head, action_t *paction);

void FreeActions(action_t *action_head);

#endif
