#include "jeu_de_test.h"

semaine_t *tete_semaine;
semaine_t *tete_semaine2;
semaine_t *tete_semaine3;
jourList_t *list_jours;
jourList_t *list_jours2;

BEGIN_TEST_GROUP(TESTS)

/*
TEST(listJours) {
   tete_semaine = createAgendaFromFile("tests/nulltest.txt");
   list_jours = createJourList(tete_semaine, "Test", 2);

    CHECK (list_jours->deb == NULL);
}

TEST(blankFile) {
   tete_semaine = createAgendaFromFile("tests/blank.txt");
   list_jours = createJourList(tete_semaine, "Test", 2);

   CHECK (list_jours->deb == NULL);
   CHECK (tete_semaine->semaine_suiv == NULL);
}

TEST(createAgenda) {
   char buffer[10];
   tete_semaine = createAgendaFromFile("tests/test_agenda.txt");
   CHECK (tete_semaine->semaine_suiv != NULL);
   CHECK (compareSem("2022","15",tete_semaine->semaine_suiv));
   CHECK (compareDates('8',"10",tete_semaine->semaine_suiv->action));
   writeName(tete_semaine->semaine_suiv->action, buffer);
   CHECK (strcmp(tete_semaine->semaine_suiv->action->nom, buffer) == 0);
}


TEST(saveListfile_test) {
   tete_semaine = createAgendaFromFile("tests/test_agenda.txt");
   saveListFile(tete_semaine, "tests/test.txt");

   int diff = system("diff tests/test_agenda.txt tests/test.txt");

   CHECK (diff == 0);
}
TEST(jourList_test) {
   tete_semaine = createAgendaFromFile("tests/test_agenda.txt");
   list_jours = createJourList(tete_semaine, "Hello", 2);

   CHECK(tete_semaine != NULL);
   CHECK(list_jours->deb[0] == '1');

   list_jours = createJourList(tete_semaine, "",2);

   CHECK(list_jours->deb[0] == '1');
   CHECK(list_jours->deb[1] == '2');
   CHECK(list_jours->deb + 1== list_jours->fin);

   list_jours = createJourList(tete_semaine, "motif_introuvable",2);
   CHECK(list_jours->deb == list_jours->fin);
   CHECK(list_jours->deb == NULL);
}*/

TEST(removeActionFromList_test)
{
    // cas 1: action non présente dans la liste:
    tete_semaine = createAgendaFromFile("tests/test_agenda.txt");
    tete_semaine2 = createAgendaFromFile("tests/test_agenda.txt");
    tete_semaine3 = createAgendaFromFile("tests/test_agenda.txt");

    semaine_t * semaine_tmp = tete_semaine2->semaine_suiv;
    removeActionFromList(tete_semaine2, "2001", "05", '1', "08");
    printf("-------calendrier témoin: ----------\n");
    printAll(tete_semaine);
    printf("-------fin calendrier témoin---------\n");
    printf("-------suppression de la tête: ----------\n");
    printAll(tete_semaine2);
    printf("-------fin suppression de la tête: ----------\n");
    printf("-------suppression semaine non présente: ----------\n");
    removeActionFromList(tete_semaine3, "3783", "15", '2', "18");
    printAll(tete_semaine3);
    printf("-------fin suppression semmaine non présente: ----------\n");

    CHECK ( semaine_tmp != tete_semaine2->semaine_suiv );
}

END_TEST_GROUP(TESTS)

int run_tests()
{
    RUN_TEST_GROUP(TESTS);
    return 0;
}
