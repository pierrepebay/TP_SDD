#include "utilities.h"

/* -------------------------------------------------------------------- */
/* printn affiche n caractères */
/* */
/* En entrée: string: une chaîne de caractères
              n: le nombre de caractères à afficher */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void printn(char *string, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", string[i]);
    }
}

/* -------------------------------------------------------------------- */
/* fprintn écrit n caractères dans un fichier*/
/* */
/* En entrée: file: fichier
              string: une chaîne de caractères
              n: le nombre de caractères à afficher */
/* En sortie: void */
/* -------------------------------------------------------------------- */
void fprintn(FILE *file, char *string, int n)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%c", string[i]);
    }
}

/* -------------------------------------------------------------------- */
/* PatternInString recherche si une chaîne de caractères comporte un motif */
/* */
/* En entrée: string: une chaîne de caractères
              motif: le motif à rechercher */
/* En sortie: 0 si le motif n'est pas présent dans string
              1 sinon */
/* -------------------------------------------------------------------- */
int PatternInString(char *string, char *motif)
{
    int res = 0;
    int len_motif = strlen(motif);
    int i = 0;
    int ok = 0;
    while (res == 0 && i < 11 - len_motif) // 11 correspond à la longueur maximale d'un nom d'action + 1
    { //on compare les caracteres un à un en avançant d'un caractère à chaque itération
        ok = 1;
        for (int j = 0; j < len_motif; j++)
        {
            if (string[i + j] != motif[j])
            { // Un des caracteres dans le sous-mot de longueur len_motif est différent de celui dans motif
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
