#include "action.h"

/* -------------------------------------------------------------------- */
/* writeDay écrit le jour de l'action en cours de traitement dans le champ psemaine->annee */
/* */
/* En entrée: psemaine: un pointeur vers une semaine, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeDay(action_t * paction, char * ligne){
    paction->jour[0] = ligne[6];
    paction->jour[1] = '\0';
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
    paction->heure[2] = '\0';
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
    paction->nom[11] = '\0';
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
int compareDates(char * jour, char * heure, action_t * action_cour){
    int jour_comp = strcmp(jour, action_cour->jour);
    int heure_comp = strcmp(heure, action_cour->heure);
    if (jour_comp == 0){
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
        if (jour_comp > 0){
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
        printf("   -- Day: %s, Hour : %s, Task Name : %s\n", cour->jour, cour->heure, cour->nom);
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