#include "action.h"
#include "week.h"

/* -------------------------------------------------------------------- */
/* writeDay écrit le day de l'action en cours de traitement dans le champ pweek->annee */
/* */
/* En entrée: pweek: un pointeur vers une week, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeDay(action_t *paction, char *ligne)
{
    paction->day = ligne[6];
}

/* -------------------------------------------------------------------- */
/* writeHour écrit l'heure de l'action en cours de traitement dans le champ pweek->annee */
/* */
/* En entrée: pweek: un pointeur vers une week, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeHour(action_t *paction, char *ligne)
{
    paction->heure[0] = ligne[7];
    paction->heure[1] = ligne[8];
}

/* -------------------------------------------------------------------- */
/* writeName écrit le nom de l'action en cours de traitement dans le champ pweek->annee */
/* */
/* En entrée: pweek: un pointeur vers une week, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeName(action_t *paction, char *ligne)
{
    for (int i = 9; i < 19; i++)
    {
        paction->nom[i - 9] = ligne[i];
    }
}

/* -------------------------------------------------------------------- */
/* compareDates compare la date d'une action avec la date donnée en paramètre */
/* */
/* En entrée: day: une chaîne de caractères représentant un day, heure: une chaîne de caractères représentant une heure, action_cour: l'action courante */
/* */
/* En sortie: 1 si les dates coïncident
2 si la date de l'action est inférieure à la date passée en paramètre
3 sinon */
/* -------------------------------------------------------------------- */
int compareDates(char day, char *heure, action_t *action_cour)
{
    int retour = 0;
    int heure_comp = strncmp(heure, action_cour->heure, LEN_HOUR);
    if (day == action_cour->day)
    {
        if (heure_comp == 0)
        {
            retour = MEME_DATE; // SAME DATE
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
        if (day > action_cour->day)
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
/* printActionList affiche la liste des actions */
/* */
/* En entrée: action_head: la tête de la liste des actions */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void printActionList(action_t *action_head)
{
    action_t *cour = action_head;
    while (cour != NULL)
    {
        printf("   -- Day: %c", cour->day);
        printf(" Hour: ");
        printn(cour->heure, LEN_HOUR);
        printf(" Task Name: ");
        printn(cour->nom, LEN_TASK_NAME);
        printf("\n"); 

        cour = cour->action_suiv;
    }
}

/* -------------------------------------------------------------------- */
/* addActionToList insère une action dans la liste des actions en guardant celle-ci triée */
/* */
/* En entrée: action_head: la tête de la liste des actions, paction : pointeur vers l'action à inserer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void addActionToList(action_t *action_head, action_t *paction)
{
    if (action_head->action_suiv == NULL)
    {
        action_head->action_suiv = paction;
    }
    else
    {
        action_t *cour = action_head->action_suiv;
        action_t *prec = action_head;
        while (cour != NULL && compareDates(paction->day, paction->heure, cour) != DATE1_INF_DATE2)
        {
            prec = cour;
            cour = cour->action_suiv;
        }
        prec->action_suiv = paction;
        paction->action_suiv = cour;
    }
}

/* -------------------------------------------------------------------- */
/* removeActionFromList supprime une action du calendrier */
/* */
/* En entrée: week_fictive: la tête fictive de la liste des weeks, annee: chaîne de caractères représentant l'année de l'action à supprimer, week: chaîne de caractères représentant la week de l'action à supprimer, day: chaîne de caractères représentant le day de l'action à supprimer, heure: chaîne de caractères représentant l'heure de l'action à supprimer  */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void removeActionFromList(week_t *week_fictive, char *annee, char *week, char day, char *heure)
{
    week_t *week_cour = week_fictive->week_suiv;
    week_t *week_prec = week_fictive;
    while (week_cour && compareSem(annee, week, week_cour) != MEME_DATE)
    {
        week_prec = week_cour;
        week_cour = week_cour->week_suiv;
    }
    if (week_cour)
    {
        action_t *action_cour = week_cour->action;
        action_t *action_prec = action_cour;
        while (action_cour && compareDates(day, heure, action_cour) != MEME_DATE)
        {
            action_prec = action_cour;
            action_cour = action_cour->action_suiv;
        }
        if (action_cour)
        {
            if (action_cour == week_cour->action)
            {
                week_cour->action = action_cour->action_suiv;
            }
            else
            {
                action_prec->action_suiv = action_cour->action_suiv;
            }
            free(action_cour);
            if (!week_cour->action)
            {
                week_prec->week_suiv = week_cour->week_suiv;
                free(week_cour);
            }
        }
    }
}

void freeActions(action_t *action_head)
{
    action_t *cour = action_head;
    action_t *tmp;
    while (cour)
    {
        tmp = cour;
        cour = cour->action_suiv;
        free(tmp);
    }
}
