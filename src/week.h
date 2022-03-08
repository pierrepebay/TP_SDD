#ifndef WEEK_HEADER_
#define WEEK_HEADER_

#include "action.h"

#define SAME_DATE 1
#define DATE1_SUP_DATE2 2
#define DATE1_INF_DATE2 3

#define LEN_YEAR 4
#define LEN_WEEK 2

typedef struct week
{
    char year[LEN_YEAR];
    char num_week[LEN_WEEK];
    action_t* action;
    struct week* next_week;
} week_t;

typedef struct dayList
{
    char* start;
    char* end;
    int MaxSize;
} dayList_t;



void WriteYear(week_t *pweek, char *ligne);

void WriteWeek(week_t *pweek, char *ligne);

int CompareWeekDates(char *year, char *num_week, week_t *week_curr);

void RemoveActionFromAgenda(week_t*, char*, char*, char, char*);

void PrintAll(week_t* week_fictive);

void AddWeekToAgenda(week_t *week_head, week_t *week_to_add);

week_t*GetWeekPtr(week_t *week_head, week_t *week_curr);

void FreeWeek(week_t* week);

#endif
