#include "jeu_de_test.h"

BEGIN_TEST_GROUP(TESTS)


TEST(listJours) {
   semaine_t* tete_semaine = createAgendaFromFile("nulltest.txt");
   jourList_t*  list_jours = createJourList(tete_semaine, "Test", 2);

	CHECK (list_jours->deb == NULL);
}


TEST(fileNotFound) {
   semaine_t* tete_semaine = createAgendaFromFile("foo.txt");
   jourList_t*  list_jours = createJourList(tete_semaine, "Test", 2);

	CHECK (list_jours->deb == NULL);
   CHECK (tete_semaine->semaine_suiv == NULL);
}

TEST(blankFile) {
   semaine_t* tete_semaine = createAgendaFromFile("blank.txt");
   jourList_t* list_jours = createJourList(tete_semaine, "Test", 2);

   CHECK (list_jours->deb == NULL);
   CHECK (tete_semaine->semaine_suiv == NULL);
}

TEST(createAgenda) {
   char buffer[10];
   semaine_t* tete_semaine = createAgendaFromFile("test_agenda.txt");
   CHECK (tete_semaine->semaine_suiv != NULL);
   CHECK (compareSem("2022","15",tete_semaine->semaine_suiv));
   CHECK (compareDates('8',"10",tete_semaine->semaine_suiv->action));
   writeName(tete_semaine->semaine_suiv->action, buffer);
   CHECK (strcmp(tete_semaine->semaine_suiv->action->nom, buffer) == 0);
}

TEST(saveListfile_test) {
   semaine_t* tete_semaine = createAgendaFromFile("test_agenda.txt");
   //saveListFile(tete_semaine, "test_agenda2.txt");
   int diff = system("diff test_agenda.txt test_agenda2.txt");

   CHECK (diff == 0);
}

END_TEST_GROUP(TESTS)


int run_tests() {
	RUN_TEST_GROUP(TESTS);
 	return 0;
}
