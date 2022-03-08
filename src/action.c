#include "action.h"
#include "week.h"

/* -------------------------------------------------------------------- */
/* WriteDay écrit le day de l'action en currs de traitement dans le champ pweek->year */
/* */
/* En entrée: pweek: un pointeur vers une week, ligne: la ligne en currs de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void WriteDay(action_t *paction, char *ligne)
{
    paction->day = ligne[6];
}

/* -------------------------------------------------------------------- */
/* WriteHour écrit l'hour de l'action en currs de traitement dans le champ pweek->year */
/* */
/* En entrée: pweek: un pointeur vers une week, ligne: la ligne en currs de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void WriteHour(action_t *paction, char *ligne)
{
    paction->hour[0] = ligne[7];
    paction->hour[1] = ligne[8];
}

/* -------------------------------------------------------------------- */
/* WriteName écrit le name de l'action en currs de traitement dans le champ pweek->year */
/* */
/* En entrée: pweek: un pointeur vers une week, ligne: la ligne en currs de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void WriteName(action_t *paction, char *ligne)
{
    for (int i = 9; i < 19; i++)
    {
        paction->name[i - 9] = ligne[i];
    }
}

/* -------------------------------------------------------------------- */
/* CompareActionDates compare la date d'une action avec la date donnée en paramètre */
/* */
/* En entrée: day: une chaîne de caractères représentant un day, hour: une chaîne de caractères représentant une hour, action_curr: l'action currante */
/* */
/* En sortie: 1 si les dates coïncident
2 si la date de l'action est inférieure à la date passée en paramètre
3 sinon */
/* -------------------------------------------------------------------- */
int CompareActionDates(char day, char *hour, action_t *action_curr)
{
    int retour = 0;
    int heure_comp = strncmp(hour, action_curr->hour, LEN_HOUR);
    if (day == action_curr->day)
    {
        if (heure_comp == 0)
        {
            retour = SAME_DATE; // SAME DATE
        }
        else
        {
            if (heure_comp > 0)
            {
                retour = DATE1_SUP_DATE2; // DATE1 > DATE2
            }
            else
            {
                retour = DATE1_INF_DATE2; // DATE 1 < DATE2
            }
        }
    }
    else
    {
        if (day > action_curr->day)
        {
            retour = DATE1_SUP_DATE2; // DATE1 > DATE2
        }
        else
        {
            retour = DATE1_INF_DATE2; // DATE 1 < DATE2
        }
    }
    return retour;
}

/* -------------------------------------------------------------------- */
/* PrintActionList affiche la liste des actions */
/* */
/* En entrée: action_head: la tête de la liste des actions */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void PrintActionList(action_t *action_head)
{
    action_t *curr = action_head;
    while (curr != NULL)
    {
        printf("   -- Day: %c", curr->day);
        printf(" Hour: ");
        printn(curr->hour, LEN_HOUR);
        printf(" Task Name: ");
        printn(curr->name, LEN_TASK_NAME);
        printf("\n");

        curr = curr->next_action;
    }
}

/* -------------------------------------------------------------------- */
/* AddActionToList insère une action dans la liste des actions en guardant celle-ci triée */
/* */
/* En entrée: action_head: la tête de la liste des actions, paction : pointeur vers l'action à inserer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void AddActionToList(action_t *action_head, action_t *paction)
{
    if (action_head->next_action == NULL)
    {
        action_head->next_action = paction;
    }
    else
    {
        action_t *curr = action_head->next_action;
        action_t *prec = action_head;
        while (curr != NULL && CompareActionDates(paction->day, paction->hour, curr) != DATE1_INF_DATE2)
        {
            prec = curr;
            curr = curr->next_action;
        }
        prec->next_action = paction;
        paction->next_action = curr;
    }
}

/* -------------------------------------------------------------------- */
/* RemoveActionFromAgenda supprime une action du calendrier */
/* */
/* En entrée: week_fictive: la tête fictive de la liste des weeks, year: chaîne de caractères représentant l'année de l'action à supprimer, week: chaîne de caractères représentant la week de l'action à supprimer, day: chaîne de caractères représentant le day de l'action à supprimer, hour: chaîne de caractères représentant l'hour de l'action à supprimer  */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void RemoveActionFromAgenda(week_t *week_fictive, char *year, char *week, char day, char *hour)
{
    week_t *week_curr = week_fictive->next_week;
    week_t *week_prec = week_fictive;
    while (week_curr && CompareWeekDates(year, week, week_curr) != SAME_DATE)
    {
        week_prec = week_curr;
        week_curr = week_curr->next_week;
    }
    if (week_curr)
    {
        action_t *action_curr = week_curr->action;
        action_t *action_prec = action_curr;
        while (action_curr && CompareActionDates(day, hour, action_curr) != SAME_DATE)
        {
            action_prec = action_curr;
            action_curr = action_curr->next_action;
        }
        if (action_curr)
        {
            if (action_curr == week_curr->action)
            {
                week_curr->action = action_curr->next_action;
            }
            else
            {
                action_prec->next_action = action_curr->next_action;
            }
            free(action_curr);
            if (!week_curr->action)
            {
                week_prec->next_week = week_curr->next_week;
                free(week_curr);
            }
        }
    }
}

void FreeActions(action_t *action_head)
{
    action_t *curr = action_head;
    action_t *tmp;
    while (curr)
    {
        tmp = curr;
        curr = curr->next_action;
        free(tmp);
    }
}
