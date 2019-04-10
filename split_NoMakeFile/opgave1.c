#include "allIncludes.h"
void opgave1 (structParticipant* _participant){
    findAndPrint("ITA", _participant);
}

void findAndPrint(char *_nation, structParticipant *_participant)
{
    int counter;

    for (counter= 0; counter< _AMOUNT_PARTICIPANT; counter++)
    {
        if (strcmp(_nation, _participant[counter].nation) == 0 && _participant[counter].age >30)
        {
            printf("%-20s %-32s | %2d %3s %3s |   %3s    %-s\n",_participant[counter].nameRace, _participant[counter].nameParticipant, _participant[counter].age, _participant[counter].nameTeam, _participant[counter].nation, _participant[counter].placement, _participant[counter].finishTime);
        }
    }
}
