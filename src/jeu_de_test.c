#include "jeu_de_test.h"

semaine_t* tete_semaine;
semaine_t* tete_semaine2;
jourList_t*  list_jours;
jourList_t*  list_jours2;


BEGIN_TEST_GROUP(TESTS)

TEST(listJours) {
   tete_semaine = createAgendaFromFile("tests/nulltest.txt");
   list_jours = createJourList(tete_semaine, "Test", 2);

	CHECK (list_jours->deb == NULL);
}


TEST(fileNotFound) {
   tete_semaine = createAgendaFromFile("tests/foo.txt");
   list_jours = createJourList(tete_semaine, "Test", 2);

	CHECK (list_jours->deb == NULL);
   CHECK (tete_semaine->semaine_suiv == NULL);
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
   freeAll(tete_semaine, NULL);
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
}

TEST(removeActionFromList_test) {
   // cas 1: action non présente dans la liste:
   tete_semaine = createAgendaFromFile("tests/test_agenda.txt");
   //removeActionFromList(tete_semaine, "2069", "12", '1', "09");
   //tete_semaine2 = createAgendaFromFile("tests/test_agenda.txt");

   int comp = compareSem(tete_semaine->semaine_suiv->annee, tete_semaine->semaine_suiv->num_semaine, tete_semaine);
   printf("%d\n",comp);
}

END_TEST_GROUP(TESTS)


int run_tests() {
	RUN_TEST_GROUP(TESTS);
 	return 0;
}
