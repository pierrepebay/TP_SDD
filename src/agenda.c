#include "agenda.h"

void ProcessLine(week_t *pweek, action_t *paction, char *ligne)
{
    WriteYear(pweek, ligne);
    WriteWeek(pweek, ligne);
    WriteDay(paction, ligne);
    WriteHour(paction, ligne);
    WriteName(paction, ligne);
}

void InsertToAgenda(week_t *week_head, week_t *week_tmp, action_t *action_curr)
{
    week_t *week_curr = NULL;
    week_curr = GetWeekPtr(week_head, week_tmp); // recherche si la semaine appartient à la liste des semaines
    if (week_curr == NULL)
    { // si la semaine n'appartient pas à la liste des semaines
        week_curr = week_tmp;
        week_curr->action = action_curr;
        AddWeekToAgenda(week_head, week_curr);
    }
    else
    { // si la semaine est déjà présente dans la liste des semaines
        AddActionToList(week_curr->action, action_curr);
        free(week_tmp); // on libère la semaine temporaire
    }
}

week_t *CreateAgendaFromFile(char *file_name)
{
    char ligne[21];
    FILE *file = fopen(file_name, "r");
    week_t *week_head = (week_t *)calloc(1, sizeof(week_t)); // tête fictive de la liste des semaines
    if (!week_head)
    {
        printf("Allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    week_head->next_week = NULL;
    action_t *action_curr;
    week_t *week_tmp;
    if (file)
    {
        fgets(ligne, 21, file);
        while (!feof(file)) // lecture du fichier et écriture de chaque ligne dans la chaîne de caractères "ligne"
        {
            action_curr = (action_t *)calloc(1, sizeof(action_t));
            week_tmp = (week_t *)calloc(1, sizeof(week_t));
            if (action_curr && week_tmp)
            {
                action_curr->next_action = NULL;
                week_tmp->next_week = NULL;
                week_tmp->action = NULL;

                // écriture des informations que contient la ligne dans les champs adéquats
                ProcessLine(week_tmp, action_curr, ligne);

                // insertion de la tâche dans le calendrier
                InsertToAgenda(week_head, week_tmp, action_curr);

                // lecture de la ligne suivante
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

void PrintDayList(dayList_t *dayList)
{
    if (dayList->start != NULL)
    {
        char *curr = dayList->start;
        while (curr <= dayList->end)
        {
            printf("%c - ", curr[0]);
            curr += 1;
        }
        if (curr != dayList->start)
        {
            printf("\n");
        }
    }
    else
    {
        printf("\n");
    }
}

void FreeDayList(dayList_t *pdayList)
{
    if (pdayList)
    {
        free(pdayList->start);
        free(pdayList);
    }
}

/* -------------------------------------------------------------------- */
/* FreeAll libère tout le calendrier */
/* */
/* En entrée: week_head: tête fictive de la liste des weeks */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void FreeAll(week_t *week_head, dayList_t *pdayList)
{
    week_t *curr = week_head->next_week;
    week_t *tmp;
    while (curr)
    {
        tmp = curr;
        curr = curr->next_week;
        FreeWeek(tmp);
    }
    free(week_head);
    FreeDayList(pdayList);
}

void WriteAgendaFile(week_t *week_head, char *file_name)
{
    FILE *file = fopen(file_name, "w");
    week_t *week_curr = week_head->next_week;
    if (file)
    {
        while (week_curr != NULL)
        {
            action_t *action_curr = week_curr->action;
            while (action_curr != NULL)
            {
                fprintn(file, week_curr->year, LEN_YEAR);
                fprintn(file, week_curr->num_week, LEN_WEEK);
                fprintf(file, "%c", action_curr->day);
                fprintn(file, action_curr->hour, LEN_HOUR);
                fprintn(file, action_curr->name, LEN_TASK_NAME);
                fprintf(file, "\n");
                action_curr = action_curr->next_action;
            }
            week_curr = week_curr->next_week;
        }
        fclose(file);
    }
    else {
        printf("Couldn't open file.\n");
        exit(EXIT_FAILURE);
    }
}

dayList_t *CreateDayList(week_t *week_head, char *motif, int maxsize)
{
    dayList_t *list = (dayList_t *)calloc(1, sizeof(dayList_t));
    char *days = (char *)calloc(maxsize, sizeof(char));
    if (!(list && days))
    {
        printf("Allocation Failed.\n");
        exit(EXIT_FAILURE);
    }
    list->MaxSize = maxsize;
    int i = 0;
    week_t *curr = week_head->next_week;
    if (curr == NULL) // Cas où l'agenda est vide
    {
        free(days);
        days = NULL;
        list->start = days;
        list->end = list->start;
    }
    else
    {
        int ListeVide = 1;
        while (curr != NULL)
        {
            action_t *action_curr = curr->action;
            while (action_curr != NULL)
            {
                if (PatternInString(action_curr->name, motif) && i < maxsize)
                {
                    days[i] = action_curr->day;
                    i++;
                    ListeVide = 0;
                }
                action_curr = action_curr->next_action;
            }
            curr = curr->next_week;
        }
        if (ListeVide) // Cas où le motif n'est pas trouvé dans l'agenda
        {
            free(days);
            days = NULL;
            list->end = days;
        }
        else
        {
            list->end = days + i - 1;
        }
        list->start = days;
    }
    return list;
}
