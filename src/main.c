#include "agenda.h"
#include "jeu_de_test.h"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        week_t *head_week = CreateAgendaFromFile(argv[1]);
        RemoveActionFromAgenda(head_week, "1998", "20", '5', "10");
        PrintAll(head_week);
        WriteAgendaFile(head_week, "WriteAgendaFile.txt");
        dayList_t *list_days = CreateDayList(head_week, "Test1", 5);
        PrintDayList(list_days);
        FreeAll(head_week, list_days);
    }
    else
    {
        run_tests();
    }
    return 0;
}
