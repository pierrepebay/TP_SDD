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
    // printf("year : %s \n", psemaine->annee);
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
    // printf("num semaineaine : %s \n", psemaine->num_semaine);
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
    int annee_comp = strcmp(annee, semaine_cour->annee);
    int numsemaine_comp = strcmp(num_semaine, semaine_cour->num_semaine);
    if (annee_comp == 0)
    {
        if (numsemaine_comp == 0)
        {
            return 1; // SAME DATE
        }
        else
        {
            if (numsemaine_comp > 0)
            {
                return 2; // DATE1 > DATE2
            }
            else
            {
                return 3; // DATE 1 < DATE2
            }
        }
    }
    else
    {
        if (annee_comp > 0)
        {
            return 2; // DATE1 > DATE2
        }
        else
        {
            return 3; // DATE 1 < DATE2
        }
    }
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
        printn(cour->annee, 4);
        printf(" Week : ");
        printn(cour->num_semaine, 2);
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
    // printf("-----adding : %s ----- \n", semaine_to_add->num_semaine);
    if (semaine_tete->semaine_suiv == NULL)
    {
        semaine_tete->semaine_suiv = semaine_to_add;
    }
    else
    {
        semaine_t *cour = semaine_tete->semaine_suiv;
        semaine_t *prec = semaine_tete;
        while (cour != NULL && compareSem(semaine_to_add->annee, semaine_to_add->num_semaine, cour) != 3)
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
    while (cour && compareSem(cour->annee, cour->num_semaine, semaine_cour) != 2)
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
    printf("freeing : %s %s\n", semaine_courante->annee, semaine_courante->num_semaine);
    free(semaine_courante);
}

/* -------------------------------------------------------------------- */
/* freeAll libère tout le calendrier */
/* */
/* En entrée: semaine_tete: tête fictive de la liste des semaines */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void freeAll(semaine_t *semaine_tete)
{
    semaine_t *cour = semaine_tete->semaine_suiv;
    semaine_t *tmp;
    while (cour)
    {
        tmp = cour;
        cour = cour->semaine_suiv;
        freeWeek(tmp);
    }
    free(semaine_tete);
}

void saveListFile(semaine_t *semaine_tete, char *file_name)
{
    FILE *file = fopen(file_name, "w");
    semaine_t *semaine_cour = semaine_tete->semaine_suiv;
    if (file)
    {
        while (semaine_cour != NULL)
        {
            action_t *action_cour = semaine_cour->action;
            while (action_cour != NULL)
            {
                fprintn(file, semaine_cour->annee, 4);
                fprintn(file, semaine_cour->num_semaine, 2);
                fprintf(file, "%c", action_cour->jour);
                fprintn(file, action_cour->heure, 2);
                fprintn(file, action_cour->nom, 10);
                fprintf(file, "\n");
                action_cour = action_cour->action_suiv;
            }
            semaine_cour = semaine_cour->semaine_suiv;
        }
    }
    fclose(file);
}

int motifPresent(char *nom, char *motif)
{
    int res = 0;
    int len_motif = strlen(motif);
    int i = 0;
    int ok = 0;
    while (i < 11 - len_motif)
    {
        ok = 1;
        for (int j = 0; j < len_motif; j++)
        {
            if (nom[i + j] != motif[j])
            {
                ok = 0;
            }
        }
        if (ok)
        {
            res = 1;
            return res;
        }
        i++;
    }
    return res;
}

jourList_t *createJourList(semaine_t *semaine_tete, char *motif, int taillemax)
{
    jourList_t *list = (jourList_t *)malloc(sizeof(jourList_t));
    list->tailleMax = taillemax;
    char *jours = (char *)malloc(taillemax * sizeof(char));
    int i = 0;
    semaine_t *cour = semaine_tete->semaine_suiv;
    while (cour != NULL)
    {
        action_t *action_cour = cour->action;
        while (action_cour != NULL)
        {
            if (motifPresent(action_cour->nom, motif))
            {
                jours[i] = action_cour->jour;
                i++;
            }
            action_cour = action_cour->action_suiv;
        }
        cour = cour->semaine_suiv;
    }
    list->deb = jours;
    list->fin = jours + i - 1;
    return list;
}
