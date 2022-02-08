#include "traitement.h"

void fgets2(char * ligne, int n, FILE * file){
    fgets(ligne,n,file);
    ligne[strlen(ligne)-1] = '\0';
}

void writeYear(semaine_t * psemaine, char * ligne){
    for (int i = 0; i < 4; i++){
        psemaine->annee[i] = ligne[i];
    }
    psemaine->annee[4] = '\0';
    //printf("year : %s \n", psemaine->annee);
}

void writeWeek(semaine_t * psemaine, char * ligne){
    for (int i = 4; i < 6; i++){
        psemaine->num_semaine[i-4] = ligne[i];
    }
    psemaine->num_semaine[2] = '\0';
    //printf("num semaineaine : %s \n", psemaine->num_semaine);
}

void writeDay(action_t * paction, char * ligne){
    paction->jour[0] = ligne[6];
    paction->jour[1] = '\0';
    //printf("num jour : %s \n", paction->jour);
}

void writeHour(action_t * paction, char * ligne){
    paction->heure[0] = ligne[7];
    paction->heure[1] = ligne[8];
    paction->heure[2] = '\0';
    //printf("hour : %s \n", paction->heure);
}

void writeName(action_t * paction, char * ligne){
    for (int i = 9; i < 19; i++){
        paction->nom[i-9] = ligne[i];
    }
    paction->nom[11] = '\0';
    //printf("nom : %s \n", paction->nom);
}

int compareDates(char * jour, char * heure, action_t * cour){
    int jour_comp = strcmp(jour, cour->jour);
    int heure_comp = strcmp(heure, cour->heure);
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

int compareSem(char * annee, char * num_semaine, semaine_t * cour){
    int annee_comp = strcmp(annee, cour->annee);
    int numsemaine_comp = strcmp(num_semaine, cour->num_semaine);
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

void printActionList(action_t * action_tete){
    action_t * cour = action_tete;
    while (cour != NULL){
        printf("   -- Day: %s, Hour : %s, Task Name : %s\n", cour->jour, cour->heure, cour->nom);
        cour = cour->action_suiv;
    }
}

void printAll(semaine_t * semaine_fictive) {
    semaine_t * cour = semaine_fictive->semaine_suiv;
    while (cour != NULL){
        printf("Year : %s , Week: %s\n",cour->annee, cour->num_semaine);
        printActionList(cour->action);
        cour = cour->semaine_suiv;
    }
} 

void addActionToList(action_t * action_tete, action_t * paction){
    //printf("-----adding : %s ----- \n", paction->nom);
    //printActionList(action_tete);
    int comp_dates;
    int ok = 1;
    if (action_tete->action_suiv == NULL){
        action_tete->action_suiv = paction;
    }
    else {
        action_t * cour = action_tete->action_suiv;
        action_t * prec = action_tete;
        while (cour != NULL && ok){
            comp_dates = compareDates(paction->jour, paction->heure, cour);
            if (comp_dates == 3){
                ok = 0;
            }
            if (ok){
                prec = cour;
                cour = cour->action_suiv;
            }
        }
        prec->action_suiv = paction;
        paction->action_suiv = cour;
    }
}

void removeActionFromList(semaine_t * semaine_fictive, char * annee, char * semaine, char * jour, char * heure){
    semaine_t * semaine_cour = semaine_fictive->semaine_suiv;
    semaine_t * semaine_prec = semaine_fictive;
    while (semaine_cour && compareSem(annee, semaine, semaine_cour) != 1)
    {
        printf("not this week : %s\n", semaine_cour->num_semaine);
        semaine_prec = semaine_cour;
        semaine_cour = semaine_cour->semaine_suiv;
    }
    if (semaine_cour){
        action_t * action_cour = semaine_cour->action;
        action_t * action_prec = action_cour;  
        while (action_cour && compareDates(jour, heure, action_cour) != 1)
        {
            printf("action now : %s\n", action_cour->nom);
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

void addSemaineToList(semaine_t * semaine_tete, semaine_t * semaine_to_add){
    //printf("-----adding : %s ----- \n", semaine_to_add->num_semaine);
    int comp_sem;
    int ok = 1;
    if (semaine_tete->semaine_suiv == NULL){
        semaine_tete->semaine_suiv = semaine_to_add;
    }
    else {
        semaine_t * cour = semaine_tete->semaine_suiv;
        semaine_t * prec = semaine_tete;
        while (cour != NULL && ok){
            comp_sem = compareSem(semaine_to_add->annee, semaine_to_add->num_semaine, cour);
            if (comp_sem == 3){
                ok = 0;
            }
            if (ok){
                prec = cour;
                cour = cour->semaine_suiv;
            }
        }
        prec->semaine_suiv = semaine_to_add;
        semaine_to_add->semaine_suiv = cour;
    }
}

semaine_t * getSemainePtr(semaine_t * semaine_tete, semaine_t * semaine_cour){
    semaine_t * cour = semaine_tete->semaine_suiv;
    while (cour)
    {
        if (!strcmp(cour->annee, semaine_cour->annee) && !strcmp(cour->num_semaine, semaine_cour->num_semaine)){
            return cour;
        }
        cour = cour->semaine_suiv;
    }
    return NULL;
}

void freeActions(action_t * action){
    action_t * cour = action;
    action_t * tmp;
    while (cour)
    {
        tmp = cour;
        cour = cour->action_suiv;
        free(tmp);
    }
    
}

void freeWeek(semaine_t * semaine_courante){
    freeActions(semaine_courante->action);
    free(semaine_courante); 
}

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