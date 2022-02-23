#include "action.h"
#include "semaine.h"

void printn(char * string, int n){
    for (int i = 0; i < n; i++){
        printf("%c", string[i]);
    }
}

void fprintn(FILE * file, char * string, int n){
    for (int i = 0; i < n; i++){
        fprintf(file, "%c", string[i]);
    }
}

/* -------------------------------------------------------------------- */
/* writeDay écrit le jour de l'action en cours de traitement dans le champ psemaine->annee */
/* */
/* En entrée: psemaine: un pointeur vers une semaine, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeDay(action_t * paction, char * ligne){
    paction->jour = ligne[6];
    //printf("num jour : %s \n", paction->jour);
}

/* -------------------------------------------------------------------- */
/* writeHour écrit l'heure de l'action en cours de traitement dans le champ psemaine->annee */
/* */
/* En entrée: psemaine: un pointeur vers une semaine, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeHour(action_t * paction, char * ligne){
    paction->heure[0] = ligne[7];
    paction->heure[1] = ligne[8];
    //printf("hour : %s \n", paction->heure);
}

/* -------------------------------------------------------------------- */
/* writeName écrit le nom de l'action en cours de traitement dans le champ psemaine->annee */
/* */
/* En entrée: psemaine: un pointeur vers une semaine, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeName(action_t * paction, char * ligne){
    for (int i = 9; i < 19; i++){
        paction->nom[i-9] = ligne[i];
    }
    //printf("nom : %s \n", paction->nom);
}

/* -------------------------------------------------------------------- */
/* compareDates compare la date d'une action avec la date donnée en paramètre */
/* */
/* En entrée: jour: une chaîne de caractères représentant un jour, heure: une chaîne de caractères représentant une heure, action_cour: l'action courante */
/* */
/* En sortie: 1 si les dates coïncident
2 si la date de l'action est inférieure à la date passée en paramètre
3 sinon */
/* -------------------------------------------------------------------- */
int compareDates(char jour, char * heure, action_t * action_cour){
    int heure_comp = strcmp(heure, action_cour->heure);
    if (jour == action_cour->jour){
        if (heure_comp == 0){
            return 1; //SAME DATE
        }
        else{
            if (heure_comp > 0){
                return 2; //DATE1 > DATE2
            }
            else{
                return 3; //DATE 1 < DATE2
            }
        }
    }
    else {
        if (jour > action_cour->jour){
            return 2; //DATE1 > DATE2
        }
        else {
            return 3; //DATE 1 < DATE2
        }
    }
}

/* -------------------------------------------------------------------- */
/* printActionList affiche la liste des actions */
/* */
/* En entrée: action_tete: la tête de la liste des actions */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void printActionList(action_t * action_tete){
    action_t * cour = action_tete;
    while (cour != NULL){
        printf("   -- Day: %c", cour->jour);
        printf(" Hour: ");
        printn(cour->heure, 2);
        printf(" Task Name: ");
        printn(cour->nom, 10);
        printf("\n");

        cour = cour->action_suiv;
    }
}

/* -------------------------------------------------------------------- */
/* addActionToList insère une action dans la liste des actions en guardant celle-ci triée */
/* */
/* En entrée: action_tete: la tête de la liste des actions, paction : pointeur vers l'action à inserer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void addActionToList(action_t * action_tete, action_t * paction){
    //printf("-----adding : %s ----- \n", paction->nom);
    //printActionList(action_tete);
    if (action_tete->action_suiv == NULL){
        action_tete->action_suiv = paction;
    }
    else {
        action_t * cour = action_tete->action_suiv;
        action_t * prec = action_tete;
        while (cour != NULL && compareDates(paction->jour, paction->heure, cour) != 3){
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
/* En entrée: semaine_fictive: la tête fictive de la liste des semaines, annee: chaîne de caractères représentant l'année de l'action à supprimer, semaine: chaîne de caractères représentant la semaine de l'action à supprimer, jour: chaîne de caractères représentant le jour de l'action à supprimer, heure: chaîne de caractères représentant l'heure de l'action à supprimer  */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void removeActionFromList(semaine_t * semaine_fictive, char * annee, char * semaine, char jour, char * heure){
    semaine_t * semaine_cour = semaine_fictive->semaine_suiv;
    semaine_t * semaine_prec = semaine_fictive;
    while (semaine_cour && compareSem(annee, semaine, semaine_cour) != 1)
    {
        semaine_prec = semaine_cour;
        semaine_cour = semaine_cour->semaine_suiv;
    }
    if (semaine_cour){
        action_t * action_cour = semaine_cour->action;
        action_t * action_prec = action_cour;
        while (action_cour && compareDates(jour, heure, action_cour) != 1)
        {
            action_prec = action_cour;
            action_cour = action_cour->action_suiv;
        }
        if (action_cour)
        {
            if (action_cour == semaine_cour->action){
                semaine_cour->action = action_cour->action_suiv;
            }
            else {
                action_prec->action_suiv = action_cour->action_suiv;
                }
            free(action_cour);
            if (!semaine_cour->action)
            {
                semaine_prec->semaine_suiv = semaine_cour->semaine_suiv;
                free(semaine_cour);
            }
        }
    }
}

void freeActions(action_t * action_tete){
    action_t * cour = action_tete;
    action_t * tmp;
    while (cour)
    {
        tmp = cour;
        cour = cour->action_suiv;
        printf("freeing: %s\n", tmp->nom);
        free(tmp);
    }
}
