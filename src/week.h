#ifndef WEEK_HEADER_
#define WEEK_HEADER_

#include "action.h"

#define MEME_DATE 1
#define DATE1_SUP_DATE2 2
#define DATE1_INF_DATE2 3

#define LEN_YEAR 4
#define LEN_WEEK 2

typedef struct week
{
    char annee[LEN_YEAR];
    char num_week[LEN_WEEK];
    action_t* action;
    struct week* week_suiv;
} week_t;

typedef struct dayList
{
    char* deb;
    char* fin;
    int tailleMax;
} dayList_t;



void writeYear(week_t*, char*);

void writeWeek(week_t*, char*);

int compareSem(char*, char*, week_t*);

void printAll(week_t*);

void removeActionFromList(week_t*, char*, char*, char, char*);

void addWeekToList(week_t*, week_t*);

week_t*getWeekPtr(week_t*, week_t*);

void freeWeek(week_t*);

#endif
