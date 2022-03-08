#ifndef ACTION_HEADER_
#define ACTION_HEADER_

#include "utilities.h"

#define LEN_DAY 1
#define LEN_HOUR 2
#define LEN_TASK_NAME 10

typedef struct action
{
    char day;
    char hour[LEN_HOUR];
    char name[LEN_TASK_NAME];
    struct action* next_action;
} action_t;

void WriteDay(action_t*, char*);

void WriteHour(action_t*, char*);

void WriteName(action_t*, char*);

int CompareActionDates(char, char*, action_t*);

void PrintActionList(action_t*);

void AddActionToList(action_t*, action_t*);

void FreeActions(action_t*);

#endif
