#include "agenda.h"

void traitementLigne(week_t *pweek, action_t *paction, char *ligne)
{
    writeYear(pweek, ligne);
    writeWeek(pweek, ligne);
    writeDay(paction, ligne);
    writeHour(paction, ligne);
    writeName(paction, ligne);
}

void insertToList(week_t *week_head, week_t *week_tmp, action_t *action_cour)
{
    week_t *week_cour = NULL;
    week_cour = getWeekPtr(week_head, week_tmp); // recherche si la week appartient à la liste des weeks
    if (week_cour == NULL)
    { // si la week n'appartient pas à la liste des weeks
        week_cour = week_tmp;
        week_cour->action = action_cour;
        addWeekToList(week_head, week_cour);
    }
    else
    { // si la week est déjà présente dans la liste des weeks
        addActionToList(week_cour->action, action_cour);
        free(week_tmp); // on libère la week temporaire
    }
}

week_t *createAgendaFromFile(char *file_name)
{
    char ligne[21];
    FILE *file = fopen(file_name, "r");
    week_t *week_head = (week_t *)calloc(1, sizeof(week_t)); // tête fictive de la liste des weeks
    if (!week_head)
    {
        printf("Allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    week_head->week_suiv = NULL;
    action_t *action_cour;
    week_t *week_tmp;
    if (file)
    {
        fgets(ligne, 21, file);
        while (!feof(file)) // lecture du fichier et écriture de chaque ligne dans la chaîne de caractères "ligne"
        {
            action_cour = (action_t *)calloc(1, sizeof(action_t));
            week_tmp = (week_t *)calloc(1, sizeof(week_t));
            if (action_cour && week_tmp)
            {
                action_cour->action_suiv = NULL;
                week_tmp->week_suiv = NULL;
                week_tmp->action = NULL;

                // écriture des informations que contient la ligne dans les champs adéquats
                traitementLigne(week_tmp, action_cour, ligne);

                // insertion de la tâche dans le calendrier
                insertToList(week_head, week_tmp, action_cour);
                fgets(ligne, 21, file);
            }
            else
            {
                printf("Allocation Failed.\n");
                exit(EXIT_FAILURE);
            }
        }
        fclose(file);
    }
    else
    {
        printf("Could not open file\n");
        exit(EXIT_FAILURE);
    }
    return week_head;
}

void printDayList(dayList_t *dayList)
{
    if (dayList->deb != NULL)
    {
        char *cour = dayList->deb;
        while (cour <= dayList->fin)
        {
            printf("%c - ", cour[0]);
            cour += 1;
        }
        if (cour != dayList->deb)
        {
            printf("\n");
        }
    }
    else
    {
        printf("\n");
    }
}

void freeDayList(dayList_t *pdayList)
{
    if (pdayList)
    {
        free(pdayList->deb);
        free(pdayList);
    }
}

/* -------------------------------------------------------------------- */
/* freeAll libère tout le calendrier */
/* */
/* En entrée: week_head: tête fictive de la liste des weeks */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void freeAll(week_t *week_head, dayList_t *pdayList)
{
    week_t *cour = week_head->week_suiv;
    week_t *tmp;
    while (cour)
    {
        tmp = cour;
        cour = cour->week_suiv;
        freeWeek(tmp);
    }
    free(week_head);
    freeDayList(pdayList);
}

void saveListFile(week_t *week_head, char *file_name)
{
    FILE *file = fopen(file_name, "w");
    week_t *week_cour = week_head->week_suiv;
    if (file)
    {
        while (week_cour != NULL)
        {
            action_t *action_cour = week_cour->action;
            while (action_cour != NULL)
            {
                fprintn(file, week_cour->annee, LEN_YEAR);
                fprintn(file, week_cour->num_week, LEN_WEEK);
                fprintf(file, "%c", action_cour->day);
                fprintn(file, action_cour->heure, LEN_HOUR);
                fprintn(file, action_cour->nom, LEN_TASK_NAME);
                fprintf(file, "\n");
                action_cour = action_cour->action_suiv;
            }
            week_cour = week_cour->week_suiv;
        }
        fclose(file);
    }
    else {
        printf("Couldn't open file.\n");
        exit(EXIT_FAILURE);
    }
}

dayList_t *createDayList(week_t *week_head, char *motif, int taillemax)
{
    dayList_t *list = (dayList_t *)calloc(1, sizeof(dayList_t));
    char *days = (char *)calloc(taillemax, sizeof(char));
    if (!(list && days))
    {
        printf("Allocation Failed.\n");
        exit(EXIT_FAILURE);
    }
    list->tailleMax = taillemax;
    int i = 0;
    week_t *cour = week_head->week_suiv;
    if (cour == NULL) // Cas où l'agenda est vide
    {
        free(days);
        days = NULL;
        list->deb = days;
        list->fin = list->deb;
    }
    else
    {
        int ListeVide = 1;
        while (cour != NULL)
        {
            action_t *action_cour = cour->action;
            while (action_cour != NULL)
            {
                if (motifPresent(action_cour->nom, motif) && i < taillemax)
                {
                    days[i] = action_cour->day;
                    i++;
                    ListeVide = 0;
                }
                action_cour = action_cour->action_suiv;
            }
            cour = cour->week_suiv;
        }
        if (ListeVide) // Cas où le motif n'est pas trouvé dans l'agenda
        {
            free(days);
            days = NULL;
            list->fin = days;
        }
        else
        {
            list->fin = days + i - 1;
        }
        list->deb = days;
    }
    return list;
}
