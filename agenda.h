#ifndef AGENDA_HEADER_
#define AGENDA_HEADER_

#include "semaine.h"
#include "action.h"

void printn(char *, int);

void fprintn(FILE *, char *, int);

void traitementLigne(semaine_t *, action_t *, char *);

void insertToList(semaine_t *, semaine_t *, action_t *);

semaine_t *createAgendaFromFile(char *);

#endif