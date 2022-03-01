#include "semaine.h"

/* -------------------------------------------------------------------- */
/* writeYear écrit l'année de l'action en cours de traitement dans le champ psemaine->annee */
/* */
/* En entrée: psemaine: un pointeur vers une semaine, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeYear(semaine_t *psemaine, char *ligne)
{
    for (int i = 0; i < 4; i++)
    {
        psemaine->annee[i] = ligne[i];
    }
}

/* -------------------------------------------------------------------- */
/* writeWeek écrit la semaine de l'action en cours de traitement dans le champ psemaine->annee */
/* */
/* En entrée: psemaine: un pointeur vers une semaine, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeWeek(semaine_t *psemaine, char *ligne)
{
    for (int i = 4; i < 6; i++)
    {
        psemaine->num_semaine[i - 4] = ligne[i];
    }
}

/* -------------------------------------------------------------------- */
/* compareSem compare l'année et le numéro de semaine d'une semaine avec l'année et le numéro de semaine passés en paramètre */
/* */
/* En entrée: annee: une chaîne de caractères représentant une annee, num_semaine: une chaîne de caractères représentant un numéro de semaine, semaine_cour: l'action courante */
/* */
/* En sortie: 1 si les dates coïncident
2 si la date de la semaine est inférieure à la date passée en paramètre
3 sinon */
/* -------------------------------------------------------------------- */
int compareSem(char *annee, char *num_semaine, semaine_t *semaine_cour)
{
    int retour = 0;
    int annee_comp = strcmp(annee, semaine_cour->annee);
    int numsemaine_comp = strcmp(num_semaine, semaine_cour->num_semaine);
    if (annee_comp == 0)
    {
        if (numsemaine_comp == 0)
        {
            retour = MEME_DATE; // SAME DATE
        }
        else
        {
            if (numsemaine_comp > 0)
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
/* printAll affiche chaque semaine avec sa liste d'actions */
/* */
/* En entrée: semaine_fictive: la tête fictive de la liste des semaines */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void printAll(semaine_t *semaine_fictive)
{
    semaine_t *cour = semaine_fictive->semaine_suiv;
    while (cour != NULL)
    {
        printf("Year : ");
        printn(cour->annee, LEN_YEAR);
        printf(" Week : ");
        printn(cour->num_semaine, LEN_WEEK);
        printf("\n");
        printActionList(cour->action);
        cour = cour->semaine_suiv;
    }
}

/* -------------------------------------------------------------------- */
/* addSemaineToList insère une semaine dans la liste des semaines en guardant celle-ci triée */
/* */
/* En entrée: semaine_tete: la tête de la liste des actions, semaine_to_add : pointeur vers la semaine à inserer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void addSemaineToList(semaine_t *semaine_tete, semaine_t *semaine_to_add)
{
    if (semaine_tete->semaine_suiv == NULL)
    {
        semaine_tete->semaine_suiv = semaine_to_add;
    }
    else
    {
        semaine_t *cour = semaine_tete->semaine_suiv;
        semaine_t *prec = semaine_tete;
        while (cour != NULL && compareSem(semaine_to_add->annee, semaine_to_add->num_semaine, cour) != DATE1_INF_DATE2)
        {
            prec = cour;
            cour = cour->semaine_suiv;
        }
        prec->semaine_suiv = semaine_to_add;
        semaine_to_add->semaine_suiv = cour;
    }
}

/* -------------------------------------------------------------------- */
/* getSemainePtr recherche une semaine spécifique dans la liste des semaines */
/* */
/* En entrée: semaine_tete: la tête de la liste des actions, semaine_cour : pointeur vers une semaine à chercher */
/* En sortie: NULL si la semaine n'est pas dans la liste des semaines, sinon retourne l'adresse de la semaine qui figure dans la liste */
/* -------------------------------------------------------------------- */
semaine_t *getSemainePtr(semaine_t *semaine_tete, semaine_t *semaine_cour)
{   
    semaine_t *cour = semaine_tete->semaine_suiv;
    while (cour && compareSem(cour->annee, cour->num_semaine, semaine_cour) != DATE1_SUP_DATE2)
    {
        if (!strcmp(cour->annee, semaine_cour->annee) && !strcmp(cour->num_semaine, semaine_cour->num_semaine))
        {
            return cour;
        }
        cour = cour->semaine_suiv;
    }
    return NULL;
}

/* -------------------------------------------------------------------- */
/* freeWeek libère une semaine */
/* */
/* En entrée: semaine_courante: pointeur vers la semaine à liberer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void freeWeek(semaine_t *semaine_courante)
{
    freeActions(semaine_courante->action);
    free(semaine_courante);
}