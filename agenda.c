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


int isLigneBlank(char * ligne){
    int blank = 0;
    for (int i = 0; i < 9; i++)
        {
        if (ligne[i] == ' '){
            i++;
            blank = 1;
        }
    }
    return blank;
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
            if (isLigneBlank(ligne) == 0){

                action_cour = (action_t *)malloc(sizeof(action_t));
                semaine_tmp = (semaine_t *)malloc(sizeof(semaine_t));

                // écriture des informations que contient la ligne dans les champs adéquats
                traitementLigne(semaine_tmp, action_cour, ligne);

                // insertion de la tâche dans le calendrier
                insertToList(semaine_tete, semaine_tmp, action_cour);
            }
        }
        fclose(file);
    }
    else {
        printf("Could not open file\n");
    }
    return semaine_tete;
}

void printJourList(jourList_t *jourList)
{
    if(jourList->deb != NULL)
    {
      char *cour = jourList->deb;
      while (cour <= jourList->fin)
      {
          printf("%c - ", cour[0]);
          cour += 1;
      }
      if (cour != jourList->deb){
          printf("\n");
      }
    }
    else
    {
      printf("\n");
    }
}

void freeJourList(jourList_t * pjourList){
    free(pjourList->deb);
    free(pjourList);
}

/* -------------------------------------------------------------------- */
/* freeAll libère tout le calendrier */
/* */
/* En entrée: semaine_tete: tête fictive de la liste des semaines */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void freeAll(semaine_t *semaine_tete, jourList_t * pjourList)
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
    freeJourList(pjourList);
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
                fprintn(file, semaine_cour->annee, LEN_YEAR);
                fprintn(file, semaine_cour->num_semaine, LEN_WEEK);
                fprintf(file, "%c", action_cour->jour);
                fprintn(file, action_cour->heure, LEN_HOUR);
                fprintn(file, action_cour->nom, LEN_TASK_NAME);
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
    while (res == 0 && i < 11 - len_motif)
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
    if (cour == NULL)
    {
      jours = NULL;
      i = 1;
    }
    while (cour != NULL)
    {
        action_t *action_cour = cour->action;
        while (action_cour != NULL)
        {
            if (motifPresent(action_cour->nom, motif) && i < taillemax)
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
