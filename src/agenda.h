#ifndef AGENDA_HEADER_
#define AGENDA_HEADER_

#include "week.h"

void traitementLigne(week_t* , action_t* , char* );

void insertToList(week_t* , week_t* , action_t* );

week_t* createAgendaFromFile(char* );

void printDayList(dayList_t* );

void freeDayList(dayList_t* );

void freeAll(week_t* , dayList_t* );

void saveListFile(week_t* , char* );

dayList_t* createDayList(week_t* , char* , int);
#endif
