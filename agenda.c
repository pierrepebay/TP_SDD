#include "agenda.h"

void printn(char *string, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", string[i]);
    }
}

void fprintn(FILE *file, char *string, int n)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%c", string[i]);
    }
}

void traitementLigne(semaine_t *psemaine, action_t *paction, char *ligne)
{
    writeYear(psemaine, ligne);
    writeWeek(psemaine, ligne);
    writeDay(paction, ligne);
    writeHour(paction, ligne);
    writeName(paction, ligne);
}

void insertToList(semaine_t *semaine_tete, semaine_t *semaine_tmp, action_t *action_cour)
{
    semaine_t *semaine_cour = getSemainePtr(semaine_tete, semaine_tmp); // recherche si la semaine appartient à la liste des semaines
    if (semaine_cour == NULL)
    { // si la semaine n'appartient pas à la liste des semaines
        semaine_cour = semaine_tmp;
        semaine_cour->action = action_cour;
        addSemaineToList(semaine_tete, semaine_cour);
    }
    else
    { // si la semaine est déjà présente dans la liste des semaines
        addActionToList(semaine_cour->action, action_cour);
        free(semaine_tmp); // on libère la semaine temporaire
    }
}

semaine_t *createAgendaFromFile(char *file_name)
{
    char ligne[21];
    FILE *file = fopen(file_name, "r");
    semaine_t *semaine_tete = (semaine_t *)malloc(sizeof(semaine_t)); // tête fictive de la liste des semaines
    action_t *action_cour;
    semaine_t *semaine_tmp;
    if (file)
    {
        while (!feof(file) && fgets(ligne, 21, file) != NULL) // lecture du fichier et écriture de chaque ligne dans la chaîne de caractères "ligne"
        {
            action_cour = (action_t *)malloc(sizeof(action_t));
            semaine_tmp = (semaine_t *)malloc(sizeof(semaine_t));

            // écriture des informations que contient la ligne dans les champs adéquats
            traitementLigne(semaine_tmp, action_cour, ligne);

            // insertion de la tâche dans le calendrier
            insertToList(semaine_tete, semaine_tmp, action_cour);
        }
        fclose(file);
    }
    return semaine_tete;
}

void printJourList(jourList_t *jourList)
{
    char *cour = jourList->deb;
    while (cour <= jourList->fin)
    {
        printf("%c - ", cour[0]);
        cour += 1;
    }
    printf("\n");
}

void freeJourList(jourList_t * pjourList){
    free(pjourList->deb);
    free(pjourList);
}