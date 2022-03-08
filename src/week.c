#include "week.h"

/* -------------------------------------------------------------------- */
/* WriteYear écrit l'année de l'action en currs de traitement dans le champ pweek->year */
/* */
/* En entrée: pweek: un pointeur vers une week, ligne: la ligne en currs de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void WriteYear(week_t *pweek, char *ligne)
{
    for (int i = 0; i < 4; i++)
    {
        pweek->year[i] = ligne[i];
    }
}

/* -------------------------------------------------------------------- */
/* WriteWeek écrit la week de l'action en currs de traitement dans le champ pweek->year */
/* */
/* En entrée: pweek: un pointeur vers une week, ligne: la ligne en currs de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void WriteWeek(week_t *pweek, char *ligne)
{
    for (int i = 4; i < 6; i++)
    {
        pweek->num_week[i - 4] = ligne[i];
    }
}

/* -------------------------------------------------------------------- */
/* CompareWeekDates compare l'année et le numéro de week d'une week avec l'année et le numéro de week passés en paramètre */
/* */
/* En entrée: year: une chaîne de caractères représentant une year, num_week: une chaîne de caractères représentant un numéro de week, week_curr: l'action currante */
/* */
/* En sortie: 1 si les dates coïncident
2 si la date de la week est inférieure à la date passée en paramètre
3 sinon */
/* -------------------------------------------------------------------- */
int CompareWeekDates(char *year, char *num_week, week_t *week_curr)
{
    int retour = 0;
    int year_comp = strncmp(year, week_curr->year, LEN_YEAR);
    int numweek_comp = strncmp(num_week, week_curr->num_week, LEN_WEEK);
    if (year_comp == 0)
    {
        if (numweek_comp == 0)
        {
            retour = SAME_DATE; // SAME DATE
        }
        else
        {
            if (numweek_comp > 0)
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
        if (year_comp > 0)
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
/* PrintAll affiche chaque week avec sa liste d'actions */
/* */
/* En entrée: week_fictive: la tête fictive de la liste des weeks */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void PrintAll(week_t *week_fictive)
{
    week_t *curr = week_fictive->next_week;
    while (curr != NULL)
    {
        printf("Year : ");
        printn(curr->year, LEN_YEAR);
        printf(" Week : ");
        printn(curr->num_week, LEN_WEEK);
        printf("\n");
        PrintActionList(curr->action);
        curr = curr->next_week;
    }
}

/* -------------------------------------------------------------------- */
/* AddWeekToAgenda insère une week dans la liste des weeks en guardant celle-ci triée */
/* */
/* En entrée: week_head: la tête de la liste des actions, week_to_add : pointeur vers la week à inserer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void AddWeekToAgenda(week_t *week_head, week_t *week_to_add)
{
    if (week_head->next_week == NULL)
    {
        week_head->next_week = week_to_add;
    }
    else
    {
        week_t *curr = week_head->next_week;
        week_t *prec = week_head;
        while (curr != NULL && CompareWeekDates(week_to_add->year, week_to_add->num_week, curr) != DATE1_INF_DATE2)
        {
            prec = curr;
            curr = curr->next_week;
        }
        prec->next_week = week_to_add;
        week_to_add->next_week = curr;
    }
}

/* -------------------------------------------------------------------- */
/* GetWeekPtr recherche une semaine spécifique dans la liste des semaines */
/* */
/* En entrée: week_head: la tête de la liste des actions, week_tmp : pointeur vers une semaine à chercher */
/* En sortie: NULL si week_tmp n'est pas dans la liste des semaines, sinon retourne l'adresse de la week qui figure dans la liste */
/* -------------------------------------------------------------------- */
week_t *GetWeekPtr(week_t *week_head, week_t *week_tmp)
{
    week_t *curr = week_head->next_week;
    week_t *res = NULL;
    while (!res && curr && CompareWeekDates(curr->year, curr->num_week, week_tmp) != DATE1_SUP_DATE2)
    {
        if (!strncmp(curr->year, week_tmp->year, LEN_YEAR) && !strncmp(curr->num_week, week_tmp->num_week, LEN_WEEK))
        {
            res = curr;
        }
        curr = curr->next_week;
    }
    return res;
}

/* -------------------------------------------------------------------- */
/* RemoveActionFromAgenda supprime une action du calendrier */
/* */
/* En entrée: week_fictive: la tête fictive de la liste des semaines, year: chaîne de caractères représentant l'année de l'action à supprimer, week: chaîne de caractères représentant la semaine de l'action à supprimer, day: chaîne de caractères représentant le day de l'action à supprimer, hour: chaîne de caractères représentant l'hour de l'action à supprimer  */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void RemoveActionFromAgenda(week_t *week_fictive, char *year, char *week, char day, char *hour)
{
    week_t *week_curr = week_fictive->next_week;
    week_t *week_prec = week_fictive;
    while (week_curr && CompareWeekDates(year, week, week_curr) != SAME_DATE) // parcours de l'agenda pour trouver la bonne semaine
    {
        week_prec = week_curr;
        week_curr = week_curr->next_week;
    }
    if (week_curr) // si la semaine est bien présente dans l'agenda
    {
        action_t *action_curr = week_curr->action;
        action_t *action_prec = action_curr;
        while (action_curr && CompareActionDates(day, hour, action_curr) != SAME_DATE) // parcours de la liste des actions pour trouver l'action à supprimer
        {
            action_prec = action_curr;
            action_curr = action_curr->next_action;
        }
        if (action_curr) // si on trouve l'action à supprimer
        {
            if (action_curr == week_curr->action) // si l'action se trouve en tête de liste
            {
                week_curr->action = action_curr->next_action;
            }
            else
            {
                action_prec->next_action = action_curr->next_action;
            }
            free(action_curr);      // on libère l'action qu'on vient de retirer du chainage
            if (!week_curr->action) // si la semaine ne comporte plus d'actions suite à la suppression de l'action
            {
                week_prec->next_week = week_curr->next_week;
                free(week_curr); // on libère la semaine
            }
        }
    }
}

/* -------------------------------------------------------------------- */
/* FreeWeek libère une semaine */
/* */
/* En entrée: week_currante: pointeur vers la semaine à liberer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void FreeWeek(week_t *week_currante)
{
    FreeActions(week_currante->action);
    free(week_currante);
}
