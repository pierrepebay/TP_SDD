#include "agenda.h"
//#include "testing.h" //à inclure si on veut utiliser les fonctions de test

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
        printf("Usage: %s <file>\n", argv[0]);
        // run_tests(); //à décommenter si on veut utiliser les fonctions de test
    }
    return 0;
}
