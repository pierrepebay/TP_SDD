#include "agenda.h"
#include "jeu_de_test.h"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        week_t *head_week = createAgendaFromFile(argv[1]);
        removeActionFromList(head_week,"1998","20",'5',"10");
        printAll(head_week);
        saveListFile(head_week, "saveListFile.txt");
        dayList_t *list_days = createDayList(head_week, "Test", 2);
        printDayList(list_days);
        freeAll(head_week, list_days);
    }
    else
    {
        run_tests();
    }
    return 0;
}
