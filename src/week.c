#include "week.h"

/* -------------------------------------------------------------------- */
/* writeYear écrit l'année de l'action en cours de traitement dans le champ pweek->annee */
/* */
/* En entrée: pweek: un pointeur vers une week, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeYear(week_t *pweek, char *ligne)
{
    for (int i = 0; i < 4; i++)
    {
        pweek->annee[i] = ligne[i];
    }
}

/* -------------------------------------------------------------------- */
/* writeWeek écrit la week de l'action en cours de traitement dans le champ pweek->annee */
/* */
/* En entrée: pweek: un pointeur vers une week, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeWeek(week_t *pweek, char *ligne)
{
    for (int i = 4; i < 6; i++)
    {
        pweek->num_week[i - 4] = ligne[i];
    }
}

/* -------------------------------------------------------------------- */
/* compareSem compare l'année et le numéro de week d'une week avec l'année et le numéro de week passés en paramètre */
/* */
/* En entrée: annee: une chaîne de caractères représentant une annee, num_week: une chaîne de caractères représentant un numéro de week, week_cour: l'action courante */
/* */
/* En sortie: 1 si les dates coïncident
2 si la date de la week est inférieure à la date passée en paramètre
3 sinon */
/* -------------------------------------------------------------------- */
int compareSem(char *annee, char *num_week, week_t *week_cour)
{
    int retour = 0;
    int annee_comp = strncmp(annee, week_cour->annee, LEN_YEAR);
    int numweek_comp = strncmp(num_week, week_cour->num_week, LEN_WEEK);
    if (annee_comp == 0)
    {
        if (numweek_comp == 0)
        {
            retour = MEME_DATE; // SAME DATE
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
        if (annee_comp > 0)
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
/* printAll affiche chaque week avec sa liste d'actions */
/* */
/* En entrée: week_fictive: la tête fictive de la liste des weeks */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void printAll(week_t *week_fictive)
{
    week_t *cour = week_fictive->week_suiv;
    while (cour != NULL)
    {
        printf("Year : ");
        printn(cour->annee, LEN_YEAR);
        printf(" Week : ");
        printn(cour->num_week, LEN_WEEK);
        printf("\n");
        printActionList(cour->action);
        cour = cour->week_suiv;
    }
}

/* -------------------------------------------------------------------- */
/* addWeekToList insère une week dans la liste des weeks en guardant celle-ci triée */
/* */
/* En entrée: week_head: la tête de la liste des actions, week_to_add : pointeur vers la week à inserer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void addWeekToList(week_t *week_head, week_t *week_to_add)
{
    if (week_head->week_suiv == NULL)
    {
        week_head->week_suiv = week_to_add;
    }
    else
    {
        week_t *cour = week_head->week_suiv;
        week_t *prec = week_head;
        while (cour != NULL && compareSem(week_to_add->annee, week_to_add->num_week, cour) != DATE1_INF_DATE2)
        {
            prec = cour;
            cour = cour->week_suiv;
        }
        prec->week_suiv = week_to_add;
        week_to_add->week_suiv = cour;
    }
}

/* -------------------------------------------------------------------- */
/* getWeekPtr recherche une week spécifique dans la liste des weeks */
/* */
/* En entrée: week_head: la tête de la liste des actions, week_cour : pointeur vers une week à chercher */
/* En sortie: NULL si la week n'est pas dans la liste des weeks, sinon retourne l'adresse de la week qui figure dans la liste */
/* -------------------------------------------------------------------- */
week_t *getWeekPtr(week_t *week_head, week_t *week_cour)
{
    week_t *cour = week_head->week_suiv;
    week_t *res = NULL;
    while (!res && cour && compareSem(cour->annee, cour->num_week, week_cour) != DATE1_SUP_DATE2)
    {
        if (!strncmp(cour->annee, week_cour->annee, LEN_YEAR) && !strncmp(cour->num_week, week_cour->num_week, LEN_WEEK))
        {
            res = cour;
        }
        cour = cour->week_suiv;
    }
    return res;
}

/* -------------------------------------------------------------------- */
/* freeWeek libère une week */
/* */
/* En entrée: week_courante: pointeur vers la week à liberer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void freeWeek(week_t *week_courante)
{
    freeActions(week_courante->action);
    free(week_courante);
}
