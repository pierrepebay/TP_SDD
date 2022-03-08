#ifndef AGENDA_HEADER_
#define AGENDA_HEADER_

/*
Ce fichier contient les fonctions s'appliquant sur les structures action
et week, c'est-à-dire celles qui gèrent la liste chainée à double niveau 
dans son intégralité.
*/

#include "week.h"

void ProcessLine(week_t *pweek, action_t *paction, char *ligne);

void InsertToAgenda(week_t *week_head, week_t *week_tmp, action_t *action_curr);

week_t *CreateAgendaFromFile(char *file_name);

void PrintDayList(dayList_t *dayList);

void FreeDayList(dayList_t *dayList);

void FreeAll(week_t *week_head, dayList_t *pdayList);

void WriteAgendaFile(week_t *week_head, char *file_name);

dayList_t *CreateDayList(week_t *week_head, char *motif, int maxsize);
#endif
