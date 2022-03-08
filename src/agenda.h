#ifndef AGENDA_HEADER_
#define AGENDA_HEADER_

#include "week.h"

void ProcessLine(week_t* , action_t* , char* );

void InsertToAgenda(week_t* , week_t* , action_t* );

week_t* CreateAgendaFromFile(char* );

void PrintDayList(dayList_t* );

void FreeDayList(dayList_t* );

void FreeAll(week_t* , dayList_t* );

void WriteAgendaFile(week_t* , char* );

dayList_t* CreateDayList(week_t* , char* , int);
#endif
