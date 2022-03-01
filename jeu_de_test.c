#include "jeu_de_test.h"

semaine_t* tete_semaine;
jourList_t*  list_jours;

BEGIN_TEST_GROUP(TESTS)



TEST(listJours) {
   tete_semaine = createAgendaFromFile("nulltest.txt");
   list_jours = createJourList(tete_semaine, "Test", 2);

	CHECK (list_jours->deb == NULL);
}


TEST(fileNotFound) {
   tete_semaine = createAgendaFromFile("foo.txt");
   list_jours = createJourList(tete_semaine, "Test", 2);

	CHECK (list_jours->deb == NULL);
   CHECK (tete_semaine->semaine_suiv == NULL);
}

TEST(blankFile) {
   tete_semaine = createAgendaFromFile("blank.txt");
   list_jours = createJourList(tete_semaine, "Test", 2);

   CHECK (list_jours->deb == NULL);
   CHECK (tete_semaine->semaine_suiv == NULL);
}

TEST(createAgenda) {
   char buffer[10];
   tete_semaine = createAgendaFromFile("test_agenda.txt");
   CHECK (tete_semaine->semaine_suiv != NULL);
   CHECK (compareSem("2022","15",tete_semaine->semaine_suiv));
   CHECK (compareDates('8',"10",tete_semaine->semaine_suiv->action));
   writeName(tete_semaine->semaine_suiv->action, buffer);
   CHECK (strcmp(tete_semaine->semaine_suiv->action->nom, buffer) == 0);
}

TEST(saveListfile_test) {
   freeAll(tete_semaine, NULL);
   tete_semaine = createAgendaFromFile("test_agenda.txt");
   saveListFile(tete_semaine, "test.txt");
   
   int diff = system("diff test_agenda.txt test.txt");

   CHECK (diff == 0);
}

TEST(jourList_test) {
   tete_semaine = createAgendaFromFile("test_agenda.txt");
   list_jours = createJourList(tete_semaine, "Hello", 2);

   CHECK(tete_semaine != NULL);
   CHECK(list_jours->deb[0] == '1');
}

END_TEST_GROUP(TESTS)


int run_tests() {
	RUN_TEST_GROUP(TESTS);
 	return 0;
}
