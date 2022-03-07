#include "jeu_de_test.h"

week_t *head_week;
week_t *head_week2;
week_t *head_week3;
dayList_t *list_days;
dayList_t *list_days2;

BEGIN_TEST_GROUP(TESTS)

/*
TEST(listDays) {
   head_week = createAgendaFromFile("tests/nulltest.txt");
   list_days = createDayList(head_week, "Test", 2);

    CHECK (list_days->deb == NULL);
}

TEST(blankFile) {
   head_week = createAgendaFromFile("tests/blank.txt");
   list_days = createDayList(head_week, "Test", 2);

   CHECK (list_days->deb == NULL);
   CHECK (head_week->week_suiv == NULL);
}

TEST(createAgenda) {
   char buffer[10];
   head_week = createAgendaFromFile("tests/test_agenda.txt");
   CHECK (head_week->week_suiv != NULL);
   CHECK (compareSem("2022","15",head_week->week_suiv));
   CHECK (compareDates('8',"10",head_week->week_suiv->action));
   writeName(head_week->week_suiv->action, buffer);
   CHECK (strcmp(head_week->week_suiv->action->nom, buffer) == 0);
}


TEST(saveListfile_test) {
   head_week = createAgendaFromFile("tests/test_agenda.txt");
   saveListFile(head_week, "tests/test.txt");

   int diff = system("diff tests/test_agenda.txt tests/test.txt");

   CHECK (diff == 0);
}
TEST(dayList_test) {
   head_week = createAgendaFromFile("tests/test_agenda.txt");
   list_days = createDayList(head_week, "Hello", 2);

   CHECK(head_week != NULL);
   CHECK(list_days->deb[0] == '1');

   list_days = createDayList(head_week, "",2);

   CHECK(list_days->deb[0] == '1');
   CHECK(list_days->deb[1] == '2');
   CHECK(list_days->deb + 1== list_days->fin);

   list_days = createDayList(head_week, "motif_introuvable",2);
   CHECK(list_days->deb == list_days->fin);
   CHECK(list_days->deb == NULL);
}*/

TEST(removeActionFromList_test)
{
    // cas 1: action non présente dans la liste:
    head_week = createAgendaFromFile("tests/test_agenda.txt");
    head_week2 = createAgendaFromFile("tests/test_agenda.txt");
    head_week3 = createAgendaFromFile("tests/test_agenda.txt");

    week_t * week_tmp = head_week2->week_suiv;
    removeActionFromList(head_week2, "2001", "05", '1', "08");
    printf("-------calendrier témoin: ----------\n");
    printAll(head_week);
    printf("-------fin calendrier témoin---------\n");
    printf("-------suppression de la tête: ----------\n");
    printAll(head_week2);
    printf("-------fin suppression de la tête: ----------\n");
    printf("-------suppression week non présente: ----------\n");
    removeActionFromList(head_week3, "3783", "15", '2', "18");
    printAll(head_week3);
    printf("-------fin suppression semmaine non présente: ----------\n");

    CHECK ( week_tmp != head_week2->week_suiv );
}

END_TEST_GROUP(TESTS)

int run_tests()
{
    RUN_TEST_GROUP(TESTS);
    return 0;
}
