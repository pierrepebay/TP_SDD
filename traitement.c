#include "traitement.h"

/* -------------------------------------------------------------------- */
/* writeYear écrit l'année de l'action en cours de traitement dans le champ psemaine->annee */
/* */
/* En entrée: psemaine: un pointeur vers une semaine, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeYear(semaine_t * psemaine, char * ligne){
    for (int i = 0; i < 4; i++){
        psemaine->annee[i] = ligne[i];
    }
    psemaine->annee[4] = '\0';
    //printf("year : %s \n", psemaine->annee);
}


/* -------------------------------------------------------------------- */
/* writeWeek écrit la semaine de l'action en cours de traitement dans le champ psemaine->annee */
/* */
/* En entrée: psemaine: un pointeur vers une semaine, ligne: la ligne en cours de traitement */
/* */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void writeWeek(semaine_t * psemaine, char * ligne){
    for (int i = 4; i < 6; i++){
        psemaine->num_semaine[i-4] = ligne[i];
    }
    psemaine->num_semaine[2] = '\0';
    //printf("num semaineaine : %s \n", psemaine->num_semaine);
}


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
/* compareSem compare l'année et le numéro de semaine d'une semaine avec l'année et le numéro de semaine passés en paramètre */
/* */
/* En entrée: annee: une chaîne de caractères représentant une annee, num_semaine: une chaîne de caractères représentant un numéro de semaine, semaine_cour: l'action courante */
/* */
/* En sortie: 1 si les dates coïncident 
2 si la date de la semaine est inférieure à la date passée en paramètre
3 sinon */
/* -------------------------------------------------------------------- */
int compareSem(char * annee, char * num_semaine, semaine_t * semaine_cour){
    int annee_comp = strcmp(annee, semaine_cour->annee);
    int numsemaine_comp = strcmp(num_semaine, semaine_cour->num_semaine);
    if (annee_comp == 0){
        if (numsemaine_comp == 0){
            return 1; //SAME DATE
        }
        else{
            if (numsemaine_comp > 0){
                return 2; //DATE1 > DATE2
            }
            else{
                return 3; //DATE 1 < DATE2
            }
        }
    }
    else {
        if (annee_comp > 0){
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
/* printAll affiche chaque semaine avec sa liste d'actions */
/* */
/* En entrée: semaine_fictive: la tête fictive de la liste des semaines */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void printAll(semaine_t * semaine_fictive) {
    semaine_t * cour = semaine_fictive->semaine_suiv;
    while (cour != NULL){
        printf("Year : %s , Week: %s\n",cour->annee, cour->num_semaine);
        printActionList(cour->action);
        cour = cour->semaine_suiv;
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
void removeActionFromList(semaine_t * semaine_fictive, char * annee, char * semaine, char * jour, char * heure){
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
} // Cas particuliers: 


/* -------------------------------------------------------------------- */
/* addSemaineToList insère une semaine dans la liste des semaines en guardant celle-ci triée */
/* */
/* En entrée: semaine_tete: la tête de la liste des actions, semaine_to_add : pointeur vers la semaine à inserer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void addSemaineToList(semaine_t * semaine_tete, semaine_t * semaine_to_add){
    //printf("-----adding : %s ----- \n", semaine_to_add->num_semaine);
    if (semaine_tete->semaine_suiv == NULL){
        semaine_tete->semaine_suiv = semaine_to_add;
    }
    else {
        semaine_t * cour = semaine_tete->semaine_suiv;
        semaine_t * prec = semaine_tete;
        while (cour != NULL && compareSem(semaine_to_add->annee, semaine_to_add->num_semaine, cour) != 3){
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
semaine_t * getSemainePtr(semaine_t * semaine_tete, semaine_t * semaine_cour){
    semaine_t * cour = semaine_tete->semaine_suiv;
    while (cour && compareSem(cour->annee, cour->num_semaine, semaine_cour) != 2)
    {
        if (!strcmp(cour->annee, semaine_cour->annee) && !strcmp(cour->num_semaine, semaine_cour->num_semaine)){
            return cour;
        }
        cour = cour->semaine_suiv;
    }
    return NULL;
}


/* -------------------------------------------------------------------- */
/* freeActions libère la liste des actions */
/* */
/* En entrée: action_tete: la tête de la liste des actions */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void freeActions(action_t * action_tete){
    action_t * cour = action_tete;
    action_t * tmp;
    while (cour)
    {
        tmp = cour;
        cour = cour->action_suiv;
        free(tmp);
    }
    
}


/* -------------------------------------------------------------------- */
/* freeWeek libère une semaine */
/* */
/* En entrée: semaine_courante: pointeur vers la semaine à liberer */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void freeWeek(semaine_t * semaine_courante){
    freeActions(semaine_courante->action);
    free(semaine_courante); 
}


/* -------------------------------------------------------------------- */
/* freeAll libère tout le calendrier */
/* */
/* En entrée: semaine_tete: tête fictive de la liste des semaines */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void freeAll(semaine_t semaine_tete){
    semaine_t * cour = semaine_tete.semaine_suiv;
    semaine_t * tmp;
    while (cour)
    {
        tmp = cour;
        cour = cour->semaine_suiv;
        freeWeek(tmp);
    }
}