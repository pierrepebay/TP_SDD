#include "testing.h"

week_t *head_week;
week_t *head_week2;
week_t *head_week3;
dayList_t *list_days;
dayList_t *list_days2;

BEGIN_TEST_GROUP(TESTS)

TEST(removeActionFromList_test)
{
    // cas 1: action non présente dans la liste:
    head_week = CreateAgendaFromFile("tests/test_agenda.txt");
    head_week2 = CreateAgendaFromFile("tests/test_agenda.txt");
    head_week3 = CreateAgendaFromFile("tests/test_agenda.txt");

    RemoveActionFromAgenda(head_week2, "2001", "05", '1', "08");
    printf("-------calendrier témoin: ----------\n");
    PrintAll(head_week);
    printf("-------end calendrier témoin---------\n");
    printf("-------suppression de la tête: ----------\n");
    PrintAll(head_week2);
    printf("-------end suppression de la tête: ----------\n");
    printf("-------suppression week non présente: ----------\n");
    RemoveActionFromAgenda(head_week3, "3783", "15", '2', "18");
    PrintAll(head_week3);
    printf("-------end suppression semmaine non présente: ----------\n");
}


TEST(saveListfile_test) {
   head_week = CreateAgendaFromFile("tests/test_agenda.txt");
   WriteAgendaFile(head_week, "tests/test.txt");

   int diff = system("diff tests/test_agenda.txt tests/test.txt");

   CHECK (diff == 0);
}

TEST(createAgenda) {
   char buffer[10];
   head_week = CreateAgendaFromFile("tests/test_agenda.txt");
   CHECK (head_week->next_week != NULL);
   CHECK (CompareWeekDates("2022","15",head_week->next_week));
   CHECK (CompareActionDates('8',"10",head_week->next_week->action));
   WriteName(head_week->next_week->action, buffer);
   CHECK (strcmp(head_week->next_week->action->name, buffer) == 0);

   head_week2 = CreateAgendaFromFile("tests/blank.txt");
   CHECK (head_week2->next_week == NULL);
}
TEST(blankFile) {
   head_week = CreateAgendaFromFile("tests/blank.txt");
   list_days = CreateDayList(head_week, "Test", 2);

   CHECK (list_days->start == NULL);
   CHECK (head_week->next_week == NULL);
}


TEST(listDays) {
   head_week = CreateAgendaFromFile("tests/nulltest.txt");
   list_days = CreateDayList(head_week, "Test", 2);

    CHECK (list_days->start == NULL);
}

TEST(dayList_test) {
   head_week = CreateAgendaFromFile("tests/test_agenda.txt");
   list_days = CreateDayList(head_week, "ello", 2);

   CHECK(head_week != NULL);
   CHECK(list_days->start[0] == '1');

   list_days = CreateDayList(head_week, "",2);

   CHECK(list_days->start[0] == '1');
   CHECK(list_days->start[1] == '7');
   CHECK(list_days->start + 1== list_days->end);

   list_days = CreateDayList(head_week, "motif_introuvable",2);
   CHECK(list_days->start == list_days->end);
   CHECK(list_days->start == NULL);
}

END_TEST_GROUP(TESTS)

int run_tests()
{
    RUN_TEST_GROUP(TESTS);
    return 0;
}
