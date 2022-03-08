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
    int tailleMax;
} dayList_t;



void WriteYear(week_t*, char*);

void WriteWeek(week_t*, char*);

int CompareWeekDates(char*, char*, week_t*);

void PrintAll(week_t*);

void RemoveActionFromAgenda(week_t*, char*, char*, char, char*);

void AddWeekToAgenda(week_t*, week_t*);

week_t*GetWeekPtr(week_t*, week_t*);

void FreeWeek(week_t*);

#endif
